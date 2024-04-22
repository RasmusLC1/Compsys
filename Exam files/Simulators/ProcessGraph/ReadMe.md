To run copy the instructions into threads.txt and sanitize them if needed, should
look something like this

P(a); P(b);
P(b); P(a);
P(c); P(c);
V(c); V(c);
V(a); V(b);
V(b); V(a);

Write make and look in output.txt for the result, if there is a negative value
then that square is a deadzone