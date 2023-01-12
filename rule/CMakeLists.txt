set(SRCS rule.c)
set (HEADERS rule.h rule.inc)

add_library(rule SHARED ${SRCS} ${HEADERS})