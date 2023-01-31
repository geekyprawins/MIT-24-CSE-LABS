set ns [new Simulator]
set nf [open out.nam w]
$ns namtrace-all $nf
$ns color 1 Blue
$ns color 2 Red

proc finish {} {
    global ns nf
    $ns flush-trace
    close $nf
    exec nam out.nam &
    exit 0
}

set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]

$ns duplex-link $n1 $n2 2Mb 20ms DropTail
$ns duplex-link $n3 $n4 1Mb 10ms DropTail
# $ns duplex-link-op $n1 $n2 orient right-up
# $ns duplex-link-op $n3 $n4 orient right-down
$ns duplex-link-op $n1 $n2 queuePos 0.5
$ns queue-limit $n1 $n2 20

set tcp [new Agent/TCP]
$ns attach-agent $n1 $tcp
$tcp set fid_ 1

set tcpsink [new Agent/TCPSink]
$ns attach-agent $n2 $tcpsink

$ns connect $tcp $tcpsink

set ftp [new Application/FTP]
$ftp attach-agent $tcp

set udp [new Agent/UDP]
$ns attach-agent $n3 $udp
$udp set fid_ 2

set null [new Agent/Null]
$ns attach-agent $n4 $null

$ns connect $udp $null

set cbr [new Application/Traffic/CBR]
$cbr set packetSize_ 500
$cbr set interval_ 0.005
$cbr set fid_ 2
$cbr attach-agent $udp


$ns at 0.5 "$ftp start"
$ns at 1.0 "$cbr start"
$ns at 4.0 "$cbr stop"
$ns at 4.5 "$ftp stop"
$ns at 5.0 "finish"
$ns run