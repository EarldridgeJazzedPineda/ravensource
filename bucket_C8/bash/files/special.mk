# On linux with glibc, we can't build a fully static bash because
# of absurd restrictions put on static linking with nss, dlopen, etc.
# So we build it dynamic but with libtinfo static.  Leaving glibc-based
# libraries like libc, libm, pthread, etc, is okay.

.if ${OPSYS} == Linux
.  if "${PLIST_SUB:MSTATIC-ON=*}" == "STATIC-ON="
CONFIGURE_ARGS:=	${CONFIGURE_ARGS:N--enable-static-link}
CFLAGS+=		-Wl,-export-dynamic
CONFIGURE_ENV+=		ac_cv_func_dlopen=no

TINFOLIBS=		${LOCALBASE}/lib/libtinfo.a \
			${LOCALBASE}/lib/db5/libdb.a \
			-lpthread

post-configure-opsys:
	${REINPLACE_CMD} -e 's|-ltinfo|${TINFOLIBS}|' ${WRKSRC}/Makefile
.  endif
.endif