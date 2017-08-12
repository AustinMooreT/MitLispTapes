#!/bin/sh
cc -o tpc2simh tpc2simh.c
echo -n >mit1.simh
echo -n >mit2.simh
echo -n >mit3.simh
echo -n >mit4.simh
./tpc2simh mit1.tpc mit1.simh
./tpc2simh mit2.tpc mit2.simh
./tpc2simh mit3.tpc mit3.simh
./tpc2simh mit4.tpc mit4.simh
exit 0

