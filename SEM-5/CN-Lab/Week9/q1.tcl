set ns [new Simulator]

set nf [open out.nam w]
$ns namtrace-all $nf

$ns color 1 Turquoise
$ns color 2 Gold

proc finish {} {
global ns nf
$ns flush-trace
close $nf
exec nam out.nam &
exit 0
}

set n0 [$ns node]
set n1 [$ns node]

$ns duplex-link $n0 $n1 10Mb 10ms DropTail

set udp [new Agent/UDP]
$ns attach-agent $n0 $udp


set null [new Agent/Null]
$ns attach-agent $n1 $null
$ns connect $udp $null
$udp set fid_ 1

set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp
$cbr set type_ CBR
$cbr set packet_size_ 1000
$cbr set rate_ 1mb
$cbr set random_ false

$ns at 0.1 "$cbr start"
$ns at 4.5 "$cbr stop"
$ns at 5.0 "finish"

$ns run