dnscrypt-proxy(8) -- A DNSCrypt forwarder
=========================================

## SYNOPSIS

`dnscrypt-proxy` [<options>]

## DESCRIPTION

**dnscrypt-proxy** accepts DNS requests, authenticates and encrypts
them using dnscrypt and forwards them to a remote dnscrypt-enabled
resolver.

Replies from the resolver are expected to be authenticated and
encrypted or else they will be discarded.

The proxy verifies the replies, decrypts them, and transparently
forwards them to the local stub resolver.

`dnscrypt-proxy` listens to `127.0.0.1` / port `53` by default.

## WARNING

**dnscrypt-proxy** is not a DNS cache. Unless your operating system
already provides a decent built-in cache (and by default, most systems
don't), clients shouldn't directly send requests to **dnscrypt-proxy**.

Intead, run a DNS cache like **Unbound**, and configure it to use
**dnscrypt-proxy** as a forwarder. Both can safely run on the same
machine as long as they use different IP addresses and/or different
ports.

## OPTIONS

  * `-a`, `--local-address=<ip>[:port]`: what local IP the daemon will listen
    to, with an optional port. The default port is 53.

  * `-d`, `--daemonize`: detach from the current terminal and run the server
    in background.

  * `-e`, `--edns-payload-size=<bytes>`: transparently add an OPT
    pseudo-RR to outgoing queries in order to enable the EDNS0
    extension mechanism. The payload size is the size of the largest
    response we accept from the resolver before retrying over TCP.
    This feature is enabled by default, with a payload size of 1252
    bytes. Any value below 512 disables it.

  * `-h`, `--help`: show usage.

  * `-k`, `--provider-key=<key>`: specify the provider public key (see below).

  * `-L`, `--resolvers-list=<file>`: path to the CSV file containing
    the list of available resolvers, and the parameters to use them.

  * `-l`, `--logfile=<file>`: log events to this file instead of the
    standard output.

  * `-m`, `--loglevel=<level>`: don't log events with priority above
    this level after the service has been started up. Default is the value
    for `LOG_INFO`.

  * `-n`, `--max-active-requests=<count>`: set the maximum number of
    simultaneous active requests. The default value is 250.

  * `-p`, `--pidfile=<file>`: write the PID number to a file.

  * `-R`, `--resolver-name=<name>`: name of the resolver to use, from
    the list of available resolvers (see `-L`).

  * `-r`, `--resolver-address=<ip>[:port]`: a DNSCrypt-capable resolver IP
    address with an optional port. The default port is 443.

  * `-t`, `--test=<margin>`: don't actually start the proxy, but check that
    a valid certificate can be retrieved from the server and that it
    will remain valid for the next <margin> minutes. The exit code is 0
    if a valid certificate can be used, 2 if no valid certificates can be used,
    3 if a timeout occurred, and 4 if a currently valid certificate is
    going to expire before <margin>. The margin is always specificied in
    minutes.

  * `-u`, `--user=<user name>`: chroot(2) to this user's home directory
    and drop privileges.

  * `-N`, `--provider-name=<FQDN>`: the fully-qualified name of the
    dnscrypt certificate provider.

  * `-T`, `--tcp-only`: always use TCP. A connection made using UDP
    will get a truncated response, so that the (stub) resolver retries using
    TCP.

  * `-V`, `--version`: show version number.

A public key is 256-bit long, and it has to be specified as a hexadecimal
string, with optional columns.

## SIMPLE USAGE EXAMPLE

    $ dnscrypt-proxy --daemonize --resolver-name=...

## ADVANCED USAGE EXAMPLE

    $ dnscrypt-proxy --provider-key=B735:1140:206F:225D:3E2B:D822:D7FD:691E:A1C3:3CC8:D666:8D0C:BE04:BFAB:CA43:FB79 --provider-name=2.dnscrypt-cert.dnscrypt.org. --resolver-address=208.67.220.220:53 --daemonize

## SEE ALSO

hostip(8)
