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
set n0 [$ns node]
set n1 [$ns node]
$ns duplex-link $n0 $n1 10Mb 10ms DropTail
set tcp [new Agent/TCP]
$ns attach-agent $n0 $tcp


set sink [new Agent/TCPSink]
$ns attach-agent $n1 $sink

$ns connect $tcp $sink
$tcp set fid_ 2

set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ftp set type_ FTP
$ns at 0.5 "$ftp start"
$ns at 4.5 "$ftp stop"
$ns at 5.0 "finish"
$ns run