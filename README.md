## IOFireWireFamily-null-deref

IOFireWireFamily-null-deref is a proof-of-concept exploit for CVE-2017-2388, a NULL pointer
derefererence in `IOFireWireUserClient` that was fixed in [macOS Sierra 10.12.4]. This
vulnerability can be triggered to cause denial of service on devices with a FireWire port.

[macOS Sierra 10.12.4]: https://support.apple.com/en-us/HT207615

### CVE-2017-2388

The function `IOFireWireUserClient::setAsyncRef_IsochChannelForceStop` did not check that the
parameter `inAsyncRef` is non-NULL before calling `bcopy` with `inAsyncRef` as the source.

### License

The IOFireWireFamily-null-deref code is released into the public domain. As a courtesy I ask that
if you reference or use any of this code you attribute it to me.
