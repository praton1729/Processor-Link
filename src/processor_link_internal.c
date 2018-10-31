/*==================================================

* File Name 	: processor_link_internal.c

* Purpose		: A driver for a VC709 platform system, based
				  around the AJIT processor. It provides the 
				  API for opening and closing fpga devices
				  along with reading and writing 32 bit numbers
				  in memory.

* Creation Date : 21-09-2018

* Last Modified : Friday 21 September 2018 05:09:16 PM IST

* Created By 	: Prathu Baronia, 14D070046 

===================================================*/

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <inttypes.h>
#include "processor_link_internal.h"

FPGA* new_fpga(char* fpga_name, char* resource_file)
{
	FPGA* pointer_to_new_fpga = (FPGA*) malloc(sizeof(FPGA));
	pointer_to_new_fpga->name = fpga_name;
	pointer_to_new_fpga->map_base = NULL;
	pointer_to_new_fpga->fd = -1;
	pointer_to_new_fpga->resource_file = resource_file; 
	return pointer_to_new_fpga;
}

FPGA* open_fpga (char* name, char* resource_file)
{
	// resource_filename should be SYS_FILE kind addresses;

	FPGA* fpga = new_fpga(name, resource_file);	

	if((fpga->fd = open(resource_file, O_RDWR | O_SYNC)) == -1) PRINT_ERROR;
	
	fpga->map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fpga->fd, RAM_BASE_ADDRESS & ~MAP_MASK);

	return fpga;
}

int close_fpga( FPGA* fpga_device)

{
	if(munmap(fpga_device->map_base, MAP_SIZE) == -1) PRINT_ERROR;
	close(fpga_device->fd);
	free(fpga_device);
	return 0;
}

// return 0 on success
int fpga_axi_write(FPGA* fpga_device, uint32_t addr, uint32_t data)
{
	void *write_addr;

	// Assuming fpga_device pointer was created but it was unable to open the device
	if((fpga_device->fd)!=0) fpga_device = open_fpga(fpga_device->name, fpga_device->resource_file);

	if((fpga_device->fd)!=0) return -1;
	
	if((fpga_device->map_base) == (void*) -1) 
	{
		PRINT_ERROR;
		return -1;
	}

	/* Write data */

	write_addr = fpga_device->map_base + (addr & MAP_MASK);

	*((uint32_t *) write_addr) = data;

	return 0;

}

// return 0 on success
int fpga_axi_read(FPGA* fpga_device, uint32_t addr,  uint32_t *data)
{
	void *read_addr;

	if((fpga_device->fd)!=0) fpga_device = open_fpga(fpga_device->name, fpga_device->resource_file);

	if((fpga_device->fd)!=0) return -1;

	if(fpga_device->map_base == (void*) -1) 
	{
		PRINT_ERROR;
		return -1;
	}

	/* Read data */

	read_addr = fpga_device->map_base + (addr & MAP_MASK);

	*data = *((uint32_t *) read_addr);

	return 0;
}
