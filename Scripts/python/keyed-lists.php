<?php

# Global variables to hold our databases
$data_summary = array();
$data_description = array();
$data_homepage = array();
$data_toplevel_ports = array();
$data_https_redirect = array();
$data_corrections = array();
$data_homepage_redirect = array();
$data_primary = array();


# procedure to set global variables.
# It must be called one for each global variable
# argument 1 must be summary|description|deadhome|toplevel
# argument 2 is the absolute path to this file
function ingest_file ($datatype, $scriptdir) {
    global
        $data_summary,
        $data_description,
        $data_homepage,
        $data_homepage_redirect,
        $data_https_redirect,
        $data_toplevel_ports,
        $data_corrections,
        $data_primary;

    $filename = "";
    $varname = "";

    switch ($datatype) {
        case "summary":
            $filename = "list.summary-override";
            $varname = "data_summary";
            break;
        case "description":
            $filename = "list.description-override";
            $varname = "data_description";
            break;
        case "deadhome":
            $filename = "list.dead-homepage";
            $varname = "data_homepage";
            break;
        case "newhome":
            $filename = "list.new-homepage";
            $varname = "data_homepage_redirect";
            break;
        case "toplevel":
            $filename = "list.python";
            $varname = "data_toplevel_ports";
            break;
        case "redirect":
            $filename = "list.https-redirect";
            $varname = "data_https_redirect";
            break;
        case "depfixes":
            $filename = "list.corrections";
            $varname = "data_corrections";
            break;
        case "primary":
            $filename = "list.primary";
            $varname = "data_primary";
            break;
        default:
            echo "illegal datatype: $datatype\n";
            echo "Must be summary|description|deadhome|toplevel|depfixes|primary\n";
            return;
    }
    $lines = file($scriptdir . "/" . $filename);
    foreach ($lines as $line) {
        $parts = explode("\t", $line);
        if (count($parts) == 1) {
            array_push ($$varname, trim($line));
        } else {
            $$varname[$parts[0]] = trim($parts[1]);
        }
    }
}


# Given a short description, it strips out common articles and ensures
# The first letter is capitalized
function make_comment ($shortdesc) {
    $copystring = $shortdesc;
    $copystring = preg_replace ("/^A /i", "", $copystring);
    $copystring = preg_replace ("/^An /i", "", $copystring);
    $copystring = preg_replace ("/^The /i", "", $copystring);
    return ucfirst($copystring);
}


# Returns the summary string to use in the specification
# Argument 1: port's namebase
# Argument 2: Original summary string
# Returns an associative array:   summary   => <43 char max summary>
#                                 truncated => boolean
function sanitize_summary ($namebase, $original_summary) {
    global $data_summary;

    $summary = "";
    $truncated = false;

    if (array_key_exists($namebase, $data_summary)) {
        $summary = $data_summary[$namebase];
    } else {
        $summary = make_comment($original_summary);
    }
    if (strlen ($summary) < 12) {
        # too short, add garbage to force a truncation alert
        # so that it can be overridden
        $summary .= "##########----------##########----------##########--";
    }
    # strip trailing periods
    $summary =  preg_replace('/[.]*$/', "", $summary);
    $truncated = strlen ($summary) > 43;
    $final_summary = $truncated ? substr($summary, 0, 43) : $summary;
    return array("summary" => $final_summary, "truncated" => $truncated);
}

# Produces test for long description.
# If there's an override, it uses that raw text,
# otherwise it uses the given description.
# Finally the text is wrapped to 75 columns and returned.
function produce_long_description
  ($namebase,
   $original_description) {
    global $data_description;

    $desctext = "";
    if (array_key_exists($namebase, $data_description)) {
        $unixtext = str_replace ('\n', "\n", $data_description[$namebase]);
        $desctext = wordwrap ($unixtext, 75) . "\n";
    } else {
        # strip out images completely
        $patt_image = '/[.][.][\s\S]*image[:][:][\s\S]*[:]target[:].*[\n]/U';
        $desctext = preg_replace($patt_image, "", $original_description);

        # flatten links
        $patt_link = array (
           '/`([[:alnum:] \s\'_]+)[<][\S\n]+[>]`__/U',
           '/`([[:alnum:] \s\'_]+)[<][\S\n]+[>]`_/U',
           '/`([[:alnum:] \s\'_]+)[<][\S\n]+[>]`/U',
           '/[[]([\s\S]+)[]][(][\s\S]+[)]/U',
           '/[[]![[]([[:alnum:] \n\s\'_)(]+)[]][]][(][\S\n]+[)]/U',
        );
        # $X = '[\1]';
        # $repl_link = array ($X, $X, $X, $X, $X);
        $desctext = preg_replace($patt_link, '[\1]', $desctext);

        # flatten html images, then anchors
        $patt_html = array (
            '/<img[\s\S]+>/U',
            '/<a[\s\S]+>([\s\S]+)<\/a>/U',
        );
        $repl_html = array ('[image]', '\1');
        $desctext = preg_replace($patt_html, $repl_html, $desctext);

        # Replace "`` ... ``" with double quotes
        $patt_quotes = "/[`][`]([[:alnum:] \s\'_]*)[`][`]/U";
        $desctext = preg_replace($patt_quotes, '\1', $desctext);

        # replace dos endings with unix endings\n
        $desctext = preg_replace('/\r\n/', "\n", $desctext);

        # remove extra carriage returns
        $desctext = preg_replace("/\n\n+/", "\n\n", $desctext);

        # Fix link spaces
        $desctext = str_replace(" ]", "]", $desctext);

        $desctext = wordwrap ($desctext . "\n", 75) . "\n";
    }
    if (substr_count ($desctext, "\n") > 100) {
        $descarray = explode("\n", $desctext);
        return join("\n", array_slice($descarray, 0, 100)) . "\n";
    } else {
        # remove extra carriage returns at the end
        $desctext = preg_replace('/\n\n+$/', "\n", $desctext);
        return $desctext;
    }
}


# Changes http:// to https://
function go_secure ($url) {
    return (str_replace("http://", "https://", $url));
}


# Check if given URL triggers repology's permanent redirection warning
function use_https_instead ($url) {
    global $data_https_redirect;

    if ( strlen($url) >= 10
      && substr($url, 0, 7) == "http://" )
    {
        $rest_of_uri = substr($url, 7);
        $components = explode("/", $rest_of_uri);
        # check if more than 2 components -- and if it matches a wildcard
        $subcomponents = explode(".", $components[0]);
        $nsc = count($subcomponents);
        if ($nsc > 2) {
            $testserver = "*."
                        . $subcomponents[$nsc - 2] . "."
                        . $subcomponents[$nsc - 1];
            if (in_array($testserver, $data_https_redirect)) {
                return true;
            }
        }
        return in_array($components[0], $data_https_redirect);
    }
    return false;
}

# Modifies homepage if necessary.
# 1) If the homepage is marked as dead, return "none"
# 2) If the homepage requires https redirection, handle that too.
# 3) If there's more than 1 value, take the first one.
# 4) If the page is on the new homepage list, use the new homepage.
function sanitize_homepage ($namebase, $original_homepage) {
    global $data_homepage, $data_homepage_redirect;

    if ($original_homepage == "UNSET" || $original_homepage == "")
    {
       return "none";
    }

    $hp_parts = explode (",", $original_homepage);
    $hp0 = trim($hp_parts[0]);
    $hp_parts = explode (" ", $hp0);
    $hp1 = trim($hp_parts[0]);

    # now replace with new homepage if it qualifies
    if (array_key_exists($hp1, $data_homepage_redirect)) {
        $hp1 = $data_homepage_redirect[$hp1];
    }

    if (strpos($hp1, "://") !== false) {
        $hp_parts = explode ("://", $hp1);
        $base_homepage = $hp_parts[1];
    } else {
        $base_homepage = $hp1;
    }

    $hplen = strlen($base_homepage);
    foreach ($data_homepage as $deadpage) {
        $deadsize = strlen($deadpage);
        $homepage_len = strlen($base_homepage);
        if ($deadsize <= $homepage_len) {
            if ($deadpage == substr($base_homepage, 0, $deadsize)) {
                return "none";
            }
        }
    }

    if (use_https_instead ($hp1)) {
       return go_secure ($hp1);
    } else {
       return $hp1;
    }
}

# Replace URL prefix on whl file urls
function wheel_site($url) {
    $prefix = "https://files.pythonhosted.org/packages/";
    $len_prefix = strlen($prefix);
    if (substr($url, 0, $len_prefix) == $prefix) {
        # The trailing "/xxx" has to be removed.
        $head = substr($url, $len_prefix);
        $elements = explode("/", $head);
        array_pop($elements);
        return "PYPIWHL/" . implode("/", $elements);
    } else {
        return $url;
    }
}

# Checks if there are any command-line arguments.
# If there are, they override the top level ports list
# Note: skip switches, such as "--force"
function set_top_level_ports($datatype, $scriptdir) {
    global
        $data_toplevel_ports,
        $argc,
        $argv;

    $arg_copy = array();
    for ($x = 1; $x < $argc; $x++) {
        $switch = (strlen ($argv[$x]) > 2 && substr($argv[$x], 0, 2) == "--");
        if (!$switch) {
            array_push($arg_copy, $argv[$x]);
        }
    }

    if (count($arg_copy)) {
        foreach ($arg_copy as $arg) {
            array_push($data_toplevel_ports, $arg);
        }
    } else {
        ingest_file($datatype, $scriptdir);
    }
}
?>
