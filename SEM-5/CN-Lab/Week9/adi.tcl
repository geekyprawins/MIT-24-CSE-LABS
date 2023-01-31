set ns [new Simulator]
set nf [open out.nam w]
$ns namtrace-all $nf

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

set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp
$cbr set packet_size_ 500
$cbr set interval_ 0.005

$ns at 1.0 "$cbr start"
$ns at 4.0 "$cbr stop"

$ns at 5.0 "finish"

$ns run
