--- sql/locks/shared_spin_lock.cc.orig	2022-08-30 03:50:14 UTC
+++ sql/locks/shared_spin_lock.cc
@@ -239,7 +239,7 @@ lock::Shared_spin_lock &lock::Shared_spi
   {
     this->spin_exclusive_lock();
   }
-#if defined(__APPLE__)
+#if defined(__APPLE__) || defined(__FreeBSD__) || defined(__DragonFly__)
   my_atomic_store64(&this->m_exclusive_owner, reinterpret_cast<int64>(self));
 #else
   my_atomic_store64(&this->m_exclusive_owner, self);
