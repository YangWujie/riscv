# 写者会被饿死:
gcc rwlock.c -lpthread -o rwlock

# 写者不会被饿死:
gcc rwlock.c -lpthread -o rwlock -DNO_WRITER_STARVATION
