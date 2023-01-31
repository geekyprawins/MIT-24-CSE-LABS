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
set n2 [$ns node]
set n3 [$ns node]

$ns duplex-link $n0 $n1 2Mb 20ms DropTail
$ns duplex-link $n2 $n3 1Mb 10ms DropTail



set tcp [new Agent/TCP]
$ns attach-agent $n0 $tcp

set sink [new Agent/TCPSink]
$ns attach-agent $n1 $sink

$ns connect $tcp $sink

set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ftp set type_ FTP

set udp [new Agent/UDP]
$ns attach-agent $n2 $udp

set null [new Agent/Null]
$ns attach-agent $n3 $null

$ns connect $udp $null

set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp
$cbr set type_ CBR

$ns at 1.0 "$ftp start"
$ns at 4.0 "$ftp stop"
$ns at 1.5 "$cbr start"
$ns at 4.0 "$cbr stop"

$ns at 5.0 "finish"

$ns run


