# Rsyslog Goa port

[Genode OS](https://genode.org/) [Goa](https://github.com/genodelabs/goa/) port of [Rsyslog](https://www.rsyslog.com/).

The runtime utilizes [test-rsyslog](../test-rsyslog) to generate log input.

## File output

Currently, two outputs are supported: by uncommenting

https://github.com/atopia/goa-utils/blob/28273e35c4131a756d167d4190038a4f9c244047/rsyslog/pkg/rsyslog/runtime#L73


The log output is directed to `/dev/log`, demonstrating `rsyslog`'s basic functionality.

## Network output

Network output when running Goa on a Linux host relies on the presence of a TAP device with IP `10.0.2.1` (see the [chrony-goa README](../chrony-goa/README.md) for an example of how to set this up).

To run a Linux instance of rsyslogd (installed via your system's package manager) as a remote target, enter the host directory and run the supplied shell script:
```
rsyslog $ cd host
rsyslog/host $ ./rsyslog.sh
```

When running the Goa package via Goa, output should now appear on the host rsyslog instance. *This requires the file output directive to be commented out, as otherwise output will not be sent to the remote instance.*
