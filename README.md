# Brute-Force-Password-Cracker

Accepts user input for a 5 letter password (a-z). Returns the password, time, and number of attempts it took to find it. Saves all entered password data and calculates average, min, max runtime for each password to report at the end of the program.

Sample output:

![Sample output image](http://i.imgur.com/OeLibDW.png "Short sample run")

```This program will guess your password.
You may only use a-z, and 1-5 characters.
Type Q to quit.
Max attempts for a password of length 5: 12356630

Please type in a password: abcde
Beginning the timer...
charSet: abcdefghijklmnopqrstuvwxyz
The password is: abcde
Total attempts: 494265
Timer has stopped.
Finished at: Tue Jul  4 17:05:30 2017
Runtime: 181.803 ms

Please type in a password: aaaaa
Beginning the timer...
charSet: abcdefghijklmnopqrstuvwxyz
The password is: aaaaa
Total attempts: 475255
Timer has stopped.
Finished at: Tue Jul  4 17:05:32 2017
Runtime: 166.115 ms

Please type in a password: zzzzz
Beginning the timer...
charSet: abcdefghijklmnopqrstuvwxyz
The password is: zzzzz
Total attempts: 12356630
Timer has stopped.
Finished at: Tue Jul  4 17:05:38 2017
Runtime: 4711.27 ms

Please type in a password: mnopq
Beginning the timer...
charSet: abcdefghijklmnopqrstuvwxyz
The password is: mnopq
Total attempts: 6197325
Timer has stopped.
Finished at: Tue Jul  4 17:05:43 2017
Runtime: 2366.51 ms

Please type in a password: a
Beginning the timer...
charSet: abcdefghijklmnopqrstuvwxyz
The password is: a
Total attempts: 1
Timer has stopped.
Finished at: Tue Jul  4 17:05:45 2017
Runtime: 1.2905 ms

Please type in a password: m
Beginning the timer...
charSet: abcdefghijklmnopqrstuvwxyz
The password is: m
Total attempts: 13
Timer has stopped.
Finished at: Tue Jul  4 17:05:47 2017
Runtime: 1.1093 ms

Please type in a password: o
Beginning the timer...
charSet: abcdefghijklmnopqrstuvwxyz
The password is: o
Total attempts: 15
Timer has stopped.
Finished at: Tue Jul  4 17:05:47 2017
Runtime: 1.3007 ms

Please type in a password: s
Beginning the timer...
charSet: abcdefghijklmnopqrstuvwxyz
The password is: s
Total attempts: 19
Timer has stopped.
Finished at: Tue Jul  4 17:05:48 2017
Runtime: 1.7316 ms

Please type in a password: ttt
Beginning the timer...
charSet: abcdefghijklmnopqrstuvwxyz
The password is: ttt
Total attempts: 14060
Timer has stopped.
Finished at: Tue Jul  4 17:05:48 2017
Runtime: 6.7852 ms

Please type in a password: vvvv
Beginning the timer...
charSet: abcdefghijklmnopqrstuvwxyz
The password is: vvvv
Total attempts: 402138
Timer has stopped.
Finished at: Tue Jul  4 17:05:50 2017
Runtime: 153.193 ms

Please type in a password: abcde
Beginning the timer...
charSet: abcdefghijklmnopqrstuvwxyz
The password is: abcde
Total attempts: 494265
Timer has stopped.
Finished at: Tue Jul  4 17:05:54 2017
Runtime: 180.896 ms

Please type in a password: bards
Beginning the timer...
charSet: abcdefghijklmnopqrstuvwxyz
The password is: bards
Total attempts: 943819
Timer has stopped.
Finished at: Tue Jul  4 17:05:57 2017
Runtime: 349.048 ms

Please type in a password: route
Beginning the timer...
charSet: abcdefghijklmnopqrstuvwxyz
The password is: route
Total attempts: 8503929
Timer has stopped.
Finished at: Tue Jul  4 17:06:01 2017
Runtime: 3239.1 ms

Please type in a password: glass
Beginning the timer...
charSet: abcdefghijklmnopqrstuvwxyz
The password is: glass
Total attempts: 3410933
Timer has stopped.
Finished at: Tue Jul  4 17:06:03 2017
Runtime: 1295.02 ms

Please type in a password: facet
Beginning the timer...
charSet: abcdefghijklmnopqrstuvwxyz
The password is: facet
Total attempts: 2761610
Timer has stopped.
Finished at: Tue Jul  4 17:06:06 2017
Runtime: 1031.18 ms

Please type in a password: mmmmm
Beginning the timer...
charSet: abcdefghijklmnopqrstuvwxyz
The password is: mmmmm
Total attempts: 6178315
Timer has stopped.
Finished at: Tue Jul  4 17:06:11 2017
Runtime: 2332.82 ms

Please type in a password: 12345
This password is invalid for the selected set!
Use up to 5 of the following characters: abcdefghijklmnopqrstuvwxyz

Please type in a password: aaaaaa
This password is invalid for the selected set!
Use up to 5 of the following characters: abcdefghijklmnopqrstuvwxyz

Please type in a password: ABCDE
This password is invalid for the selected set!
Use up to 5 of the following characters: abcdefghijklmnopqrstuvwxyz

Please type in a password: r.oot
This password is invalid for the selected set!
Use up to 5 of the following characters: abcdefghijklmnopqrstuvwxyz

Please type in a password: q
Average runtime: 1001.2ms for 16 passwords.
Min runtime: 1.1093ms to find [m] in 13 attempts.
Max runtime: 4711.27ms to find [zzzzz] in 12356630 attempts.
Average pw length: 3.50 characters.
Printing password data:
181.80ms to find [abcde] in 494265 attempts.
166.12ms to find [aaaaa] in 475255 attempts.
4711.27ms to find [zzzzz] in 12356630 attempts.
2366.51ms to find [mnopq] in 6197325 attempts.
1.29ms to find [a] in 1 attempts.
1.11ms to find [m] in 13 attempts.
1.30ms to find [o] in 15 attempts.
1.73ms to find [s] in 19 attempts.
6.79ms to find [ttt] in 14060 attempts.
153.19ms to find [vvvv] in 402138 attempts.
180.90ms to find [abcde] in 494265 attempts.
349.05ms to find [bards] in 943819 attempts.
3239.10ms to find [route] in 8503929 attempts.
1295.02ms to find [glass] in 3410933 attempts.
1031.18ms to find [facet] in 2761610 attempts.
2332.82ms to find [mmmmm] in 6178315 attempts.

Press any key to continue . . .
```
