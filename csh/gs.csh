set k0=4c1a7217a218cf6daa603c4a39736301
set k1=045a77611c9461c0bc6a82f746820642
set k2=379842734c2da8b5000cd46fac876344
set k3=4570e90ccb0510ea2322a63864d71d0f
set k4=f939198ba70f0d89190fd0982a469c1d
set k5=22b25dbe1b6f050377899905bea5dd89
set k6=3b8ea56b186ffed06f256bb10c511542
set k7=7bf788f82a5048ddd465bd35adf8aab1
set k8=0de363df22aa85691fb4f5aafe4c27bc
set k9=dd7125d83dddb15ff81272c7af81d7c1

set p10=f183f2a4
set p11=566a4baa
set p12=71477d5c
set p13=63dda331
set p14=f3ada9de
set p15=a07b030e
set p16=33a77eda
set p17=f7122f8c
set p18=e9d8c095
set p19=1e571881

set p20=0d5fe07d
set p21=bd61f322
set p22=e45a5594
set p23=69b832d1
set p24=822742f9
set p25=b9cf3a66
set p26=65cf356f
set p27=0c5a1939
set p28=604adc54
set p29=0e9e3654

set p0=430a8ff4
set p1=ee790d2c
set p2=812af697
set p3=613eb046
set p4=6df01677
set p5=acab4c5e
set p6=556103d4
set p7=2d521621
set p8=2ee56d4c
set p9=4cac36b9

#(A) tablecheck (+9 points, +1 points for each correct case)
#	Note: should generate no output

	set srcdir=~csci531/public/cs531/hw6

	foreach f (0 1 2 3 4 5 6 7 8)
		echo "==> $srcdir/f$f.tbl"
		./hw6 tablecheck -t=$srcdir/f$f.tbl
	end

#(B) modprod (+18 points, +2 for each correct answer)

	set srcdir=~csci531/public/cs531/hw6
	/bin/rm -f f?.mp

        ./hw6 modprod -p1=$p10 -p2=$p20 > f0.mp
        ./hw6 modprod -p1=$p11 -p2=$p21 > f1.mp
        ./hw6 modprod -p1=$p12 -p2=$p22 > f2.mp
        ./hw6 modprod -p1=$p13 -p2=$p23 > f3.mp
        ./hw6 modprod -p1=$p14 -p2=$p24 > f4.mp
        ./hw6 modprod -p1=$p15 -p2=$p25 > f5.mp
        ./hw6 modprod -p1=$p16 -p2=$p26 > f6.mp
        ./hw6 modprod -p1=$p17 -p2=$p27 > f7.mp
        ./hw6 modprod -p1=$p18 -p2=$p28 > f8.mp

	foreach f (0 1 2 3 4 5 6 7 8)
		echo "==> $srcdir/f$f.mp"
		diff f$f.mp $srcdir/f$f.mp
	end

	/bin/rm -f f?.mp

#(C) keyexpand (+10 points, +1 for each correct answer)

	set srcdir=~csci531/public/cs531/hw6
	/bin/rm -f f?.ke

	./hw6 keyexpand -k=$k0 -t=$srcdir/f0.tbl > f0.ke
	./hw6 keyexpand -k=$k1 -t=$srcdir/f1.tbl > f1.ke
	./hw6 keyexpand -k=$k2 -t=$srcdir/f2.tbl > f2.ke
	./hw6 keyexpand -k=$k3 -t=$srcdir/f3.tbl > f3.ke
	./hw6 keyexpand -k=$k4 -t=$srcdir/f4.tbl > f4.ke
	./hw6 keyexpand -k=$k5 -t=$srcdir/f5.tbl > f5.ke
	./hw6 keyexpand -k=$k6 -t=$srcdir/f6.tbl > f6.ke
	./hw6 keyexpand -k=$k7 -t=$srcdir/f7.tbl > f7.ke
	./hw6 keyexpand -k=$k8 -t=$srcdir/f8.tbl > f8.ke
	./hw6 keyexpand -k=$k9 -t=$srcdir/f9.tbl > f9.ke

	foreach f (0 1 2 3 4 5 6 7 8 9)
		echo "==> $srcdir/f$f.ke"
		diff f$f.ke $srcdir/f$f.ke
	end

	/bin/rm -f f?.ke

#(D) encrypt (+20 points, +2 for each correct answer)

        set srcdir=~csci531/public/cs531/hw6
	/bin/rm -f f?.enc

	./hw6 encrypt -k=$k0 -t=$srcdir/f0.tbl $srcdir/f0 > f0.enc
	./hw6 encrypt -k=$k1 -t=$srcdir/f1.tbl $srcdir/f1 > f1.enc
	./hw6 encrypt -k=$k2 -t=$srcdir/f2.tbl $srcdir/f2 > f2.enc
	./hw6 encrypt -k=$k3 -t=$srcdir/f3.tbl $srcdir/f3 > f3.enc
	./hw6 encrypt -k=$k4 -t=$srcdir/f4.tbl $srcdir/f4 > f4.enc

	cat $srcdir/f5 | ./hw6 encrypt -k=$k5 -t=$srcdir/f5.tbl > f5.enc
	cat $srcdir/f6 | ./hw6 encrypt -k=$k6 -t=$srcdir/f6.tbl > f6.enc
	cat $srcdir/f7 | ./hw6 encrypt -k=$k7 -t=$srcdir/f7.tbl > f7.enc
	cat $srcdir/f8 | ./hw6 encrypt -k=$k8 -t=$srcdir/f8.tbl > f8.enc
	cat $srcdir/f9 | ./hw6 encrypt -k=$k9 -t=$srcdir/f9.tbl > f9.enc

	foreach f (0 1 2 3 4 5 6 7 8 9)
		echo "==> $srcdir/f$f.enc"
		diff f$f.enc $srcdir/f$f.enc
	end

	/bin/rm -f f?.enc

#(E) decrypt (+20 points, +2 for each correct answer)

        set srcdir=~csci531/public/cs531/hw6
	/bin/rm -f f?.dec

	./hw6 decrypt -k=$k0 -t=$srcdir/f0.tbl $srcdir/f0 > f0.dec
	./hw6 decrypt -k=$k1 -t=$srcdir/f1.tbl $srcdir/f1 > f1.dec
	./hw6 decrypt -k=$k2 -t=$srcdir/f2.tbl $srcdir/f2 > f2.dec
	./hw6 decrypt -k=$k3 -t=$srcdir/f3.tbl $srcdir/f3 > f3.dec
	./hw6 decrypt -k=$k4 -t=$srcdir/f4.tbl $srcdir/f4 > f4.dec

	cat $srcdir/f5 | ./hw6 decrypt -k=$k5 -t=$srcdir/f5.tbl > f5.dec
	cat $srcdir/f6 | ./hw6 decrypt -k=$k6 -t=$srcdir/f6.tbl > f6.dec
	cat $srcdir/f7 | ./hw6 decrypt -k=$k7 -t=$srcdir/f7.tbl > f7.dec
	cat $srcdir/f8 | ./hw6 decrypt -k=$k8 -t=$srcdir/f8.tbl > f8.dec
	cat $srcdir/f9 | ./hw6 decrypt -k=$k9 -t=$srcdir/f9.tbl > f9.dec

	foreach f (0 1 2 3 4 5 6 7 8 9)
		echo "==> $srcdir/f$f"
		diff f$f.dec $srcdir/f$f.dec
	end

	/bin/rm -f f?.dec

#(F) inverse (+20 points, +2 for each correct answer)

	set srcdir=~csci531/public/cs531/hw6
	/bin/rm -f f?.inv

        ./hw6 inverse -p=$p0 > f0.inv
        ./hw6 inverse -p=$p1 > f1.inv
        ./hw6 inverse -p=$p2 > f2.inv
        ./hw6 inverse -p=$p3 > f3.inv
        ./hw6 inverse -p=$p4 > f4.inv
        ./hw6 inverse -p=$p5 > f5.inv
        ./hw6 inverse -p=$p6 > f6.inv
        ./hw6 inverse -p=$p7 > f7.inv
        ./hw6 inverse -p=$p8 > f8.inv
        ./hw6 inverse -p=$p9 > f9.inv

	foreach f (0 1 2 3 4 5 6 7 8 9)
		echo "==> $srcdir/f$f.inv"
		diff f$f.inv $srcdir/f$f.inv
	end

	/bin/rm -f f?.inv



#Bad commandline : -1 point each for each not handling properly
                # need some sort of error output to indicate that the command
                #     cannot be completed, it does not have to exactly the
                #     error indicated below, just something reasonable to inform
                #     the user about the error condition
                # please note that commandline parsing is separate from
                #     other functionalities, so even though a student has
                #     declared that certain part of the assignments is not
                #     imlemented, commandling parsing still needs to be done
                #     for those commands
                ./hw6
#                    (malformed command)
                ./hw6 tablecheck -t=$srcdir/f300.tbl
#                    (invalid P, too many terms in the poly)
                ./hw6 tablecheck -t=$srcdir/f301.tbl
#                    (missing INVP)
                ./hw6 tablecheck -t=$srcdir/f302.tbl
#                    (invalid characters in INVP)
                ./hw6 tablecheck -t=$srcdir/f303.tbl
#                    (invalid S-box, wrong number of entries)
                ./hw6 tablecheck -t=$srcdir/f304.tbl
#                    (invalid S-box, repeated entries)
		./hw6 modprod -p1=a403e5bf
#                    (malformed command)
		set k0=c0ec442dfea83c54620fa12e1df2d66c
		set k1=a796938514f5a652789c20f1c011b747
		set k2=eed3d84d3e7df891f5b27f96778b1ee0
		set k3=d93f470073789ee7e136ebcdc7655d80
		set k4=3271ae586cd7f2d56eab1ee373414e97
		set k10=b1b791b2b7284b052fac505989f1554
		./hw6 keyexpand -k=$k10 -t=$srcdir/f0.tbl
#                    (bad key, not enough characters)
                ./hw6 encrypt -k=$k0 -t=/home/scf-22/csci531/_login
#                    (cannot open table file)
                ./hw6 encrypt -k=$k0 -t=/etc/passwd
#                    (malformed table file)
                ./hw6 decrypt -k=$k1 -t=/home/scf-22/csci531/_login
#                    (cannot open table file)
                ./hw6 decrypt -k=$k1 -t=/etc/passwd
#                    (malformed table file)
		./hw6 inverse -p=a403e5bf22
#                    (bad poly)
		./hw6 inverse -p=a4z3e5bf
#                    (invalid poly)


