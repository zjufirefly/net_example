server_srcs:=server.c
server_objs:=$(server_srcs:.c=.o)
server_deps:=$(server_srcs:.c=.d)

client_srcs:=client.c
client_objs:=$(client_srcs:.c=.o)
client_deps:=$(client_srcs:.c=.d)


CFLAGS=-c -g -w

.PHONY:all
all:server client

server:$(server_objs) common.o
	gcc -o $@ $^
client:$(client_objs) common.o
	gcc -o $@ $^

common.o:common.c unp.h
	gcc $(CFLAGS) -o $@ $<

-include $(server_deps)
$(server_objs):%.o:%.c
	gcc $(CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -o $@ $<
-include $(client_deps)
$(client_objs):%.o:%.c
	gcc $(CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -o $@ $<


.PHONY: clean
clean:
	rm -rf server
	rm -rf client
	rm -rf *.o *.d


