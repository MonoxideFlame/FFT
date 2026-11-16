# What is in it?



Just my own exploration of the various FFT (fast fourier transform) algorithms. 

I was interested also in the number theorertic variant, done over the ring Z(2^64 - 2^32 + 1)

This ring was chosen for an unsigned 64 bit integer. A Fermat transform would not work for 64 bits, as there would need to be lots more
space dedicated to holding that one extra code. A 33 or 65 bit word is awkward. However, for really large integers, these kinds
of transforms would be fine.  

Right now, for a 64 bit depth, this is fine. I have it convolving and decimating a sequence over and over again to create a gaussian pulse.
It seems to work fine. It also showcases the Central Limit Theorem too. 

If I were to increase the size of the transform to include thousands of possible digits, then a Schoenhage-Strassen implementation can take advantage of this. 















