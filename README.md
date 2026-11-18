# What is in it?



Just my own exploration of the various FFT (fast fourier transform) algorithms. 

I was interested also in the number theorertic variant, done over the ring Z(2^64 - 2^32 + 1)

This ring was chosen for an unsigned 64 bit integer. Its prime too, so I get (2^32 - 1)2^32 possible principle roots. Meaning I can do a 2-radix transform up to 4 Billion wide. 

A Fermat transform would not work well for 64 bits, as there would need to be lots more
space dedicated to holding that one extra code. A 33 or 65 bit word is awkward. However, for really large integers, I would need to generalize to either a fermat or mersenne ring.

Right now, for a 64 bit depth, this is fine. I have it convolving and decimating a sequence over and over again to create a gaussian pulse.
It seems to work. It also showcases the Central Limit Theorem too. 


In the future, I could base a Schoenhage-Strassen implementation off of this. 















