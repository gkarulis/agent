Unofficial Linux agent for OCS Inventory NG
=====
A couple of years ago, where I work, we started using [OCS Inventory NG](http://www.ocsinventory-ng.org), which
is a really useful application in enterprises. It allows system administrators to inventory servers and workstations,
in order to plan obsolescenses and investments.
In the last two years, we also started using [Thinstation](http://www.thinstation.org) to recycle old computers
as Citrix terminals, by booting them via PXE.
Unfortunately, the OCS Inventory Agent for Unix is written in Perl. The Perl interpreter is quite big (~16MB) and
can't be put into the Thinstation images without getting a performance hit on booting. Moreover, the agent doesn't
work on a system with a read only filesystem (actually, the filesystem is read-write, but changes are lost 
when the terminal is powered off, since it's a in-RAM filesystem).
So I decided to write a small agent in C++ to be able to inventory also those machines which I was not able to do with the official agent.
The agent is not complete yet, but it can already produce an incomplete inventory of the machine and send it to the 
OCSInventory server, or save it locally.
The program weights around 250kb on disk for now, and it only has zlib as dependency, which is already present on any
Thinstation installation.
It also uses  [tinyxml2](http://www.grinninglizard.com/tinyxml2), a very small and efficient XML parsing/writing library, linked statically into the executable.

    Usage:  
    -h [--help]         : Print usage  
    -c [--conf]         : Specify configuration file  
    -s [--server]       : Specify OCSInventory server url
    If no server is specified, either via the -s option or via the
    configuration file (option -c), the program will write a local
    inventory in the current working directory.
    Examples:  
        ocsinventory-agent --conf /etc/ocsinventory-ng.conf  
        ocsinventory-agent --server http://ocsinventory-ng/ocsinventory  
