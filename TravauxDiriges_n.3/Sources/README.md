

# TP3 de Guerillon Tristan

`pandoc -s --toc tp2.md --css=./github-pandoc.css -o tp2.html`





## lscpu
Architecture:                    x86_64
CPU op-mode(s):                  32-bit, 64-bit
Byte Order:                      Little Endian
Address sizes:                   39 bits physical, 48 bits virtual
CPU(s):                          12
On-line CPU(s) list:             0-11
Thread(s) per core:              2
Core(s) per socket:              6
Socket(s):                       1
NUMA node(s):                    1
Vendor ID:                       GenuineIntel
CPU family:                      6
Model:                           158
Model name:                      Intel(R) Core(TM) i7-8750H CPU @ 2.20GHz
Stepping:                        10
CPU MHz:                         840.015
CPU max MHz:                     2200,0000
CPU min MHz:                     800,0000
BogoMIPS:                        4401.32
Virtualization:                  VT-x
L1d cache:                       192 KiB
L1i cache:                       192 KiB
L2 cache:                        1,5 MiB
L3 cache:                        9 MiB
NUMA node0 CPU(s):               0-11
Vulnerability Itlb multihit:     KVM: Mitigation: VMX disabled
Vulnerability L1tf:              Mitigation; PTE Inversion; VMX conditional 
                                 cache flushes, SMT vulnerable
Vulnerability Mds:               Mitigation; Clear CPU buffers; SMT vulnerab
                                 le
Vulnerability Meltdown:          Mitigation; PTI
Vulnerability Spec store bypass: Mitigation; Speculative Store Bypass disabl
                                 ed via prctl and seccomp
Vulnerability Spectre v1:        Mitigation; usercopy/swapgs barriers and __
                                 user pointer sanitization
Vulnerability Spectre v2:        Mitigation; Full generic retpoline, IBPB co
                                 nditional, IBRS_FW, STIBP conditional, RSB 
                                 filling
Vulnerability Srbds:             Mitigation; Microcode
Vulnerability Tsx async abort:   Not affected
Flags:                           fpu vme de pse tsc msr pae mce cx8 apic sep
                                  mtrr pge mca cmov pat pse36 clflush dts ac
                                 pi mmx fxsr sse sse2 ss ht tm pbe syscall n
                                 x pdpe1gb rdtscp lm constant_tsc art arch_p
                                 erfmon pebs bts rep_good nopl xtopology non
                                 stop_tsc cpuid aperfmperf pni pclmulqdq dte
                                 s64 monitor ds_cpl vmx est tm2 ssse3 sdbg f
                                 ma cx16 xtpr pdcm pcid sse4_1 sse4_2 x2apic
                                  movbe popcnt tsc_deadline_timer aes xsave 
                                 avx f16c rdrand lahf_lm abm 3dnowprefetch c
                                 puid_fault epb invpcid_single pti ssbd ibrs
                                  ibpb stibp tpr_shadow vnmi flexpriority ep
                                 t vpid ept_ad fsgsbase tsc_adjust bmi1 avx2
                                  smep bmi2 erms invpcid mpx rdseed adx smap
                                  clflushopt intel_pt xsaveopt xsavec xgetbv
                                 1 xsaves dtherm ida arat pln pts hwp hwp_no
                                 tify hwp_act_window hwp_epp md_clear flush_
                                 l1d


## Produit scalaire 

*Expliquer les paramètres, les fichiers, l'optimisation de compil, NbSamples, ...*

OMP_NUM    | samples=1024 | 
-----------|--------------|----------
séquentiel |   0.199
1          |   0.197
2          |   0.106 
3          |   0.081 
4          |   0.072 
8          |   0.069 


*Discuter sur ce qu'on observe, la logique qui s'y cache.*

L'execution est plus rapide pour le omp mais plus lent pour le threads C++ par rapport au non threadé.



## Produit matrice-matrice



### Permutation des boucles

*Expliquer comment est compilé le code (ligne de make ou de gcc) : on aura besoin de savoir l'optim, les paramètres, etc. Par exemple :*

`make TestProduct.exe && ./TestProduct.exe 1024`


  ordre           | time    | MFlops  | MFlops(n=2048) 
------------------|---------|---------|----------------
i,j,k (origine)   | 2.73764 | 782.476 |                
j,i,k             |  |  |    
i,k,j             |  |  |    
k,i,j             |  |  |    
j,k,i             |  |  |    
k,j,i             |  |  |    


*Discussion des résultats*



### OMP sur la meilleure boucle 

`make TestProduct.exe && OMP_NUM_THREADS=8 ./TestProduct.exe 1024`

  OMP_NUM         | MFlops  | MFlops(n=2048) | MFlops(n=512)  | MFlops(n=4096)
------------------|---------|----------------|----------------|---------------
1                 |  |
2                 |  |
3                 |  |
4                 |  |
5                 |  |
6                 |  |
7                 |  |
8                 |  |




### Produit par blocs

`make TestProduct.exe && ./TestProduct.exe 1024`

  szBlock         | MFlops  | MFlops(n=2048) | MFlops(n=512)  | MFlops(n=4096)
------------------|---------|----------------|----------------|---------------
origine (=max)    |  |
32                |  |
64                |  |
128               |  |
256               |  |
512               |  | 
1024              |  |




### Bloc + OMP



  szBlock      | OMP_NUM | MFlops  | MFlops(n=2048) | MFlops(n=512)  | MFlops(n=4096)
---------------|---------|---------|------------------------------------------------
A.nbCols       |  1      |         | 
512            |  8      |         | 







# Tips 

```
	env 
	OMP_NUM_THREADS=4 ./dot_product.exe
```

```
    $ for i in $(seq 1 4); do elap=$(OMP_NUM_THREADS=$i ./TestProductOmp.exe|grep "Temps CPU"|cut -d " " -f 7); echo -e "$i\t$elap"; done > timers.out
```
