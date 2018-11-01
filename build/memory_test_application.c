
/*=========================================

* File Name : test_application.c

* Purpose 	: A small application which 
			  performs memory read and writes.

* Creation Date : 31-10-2018

* Last Modified : Wednesday 31 October 2018 12:38:43 PM IST

* Created By : Prathu Baronia, 14D070046 

==========================================*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<inttypes.h>
#include<math.h>
#include<assert.h>
#include "processor_link.h"

int main(int argc, char* argv)
{
	uint32_t address   = 0x00;
	uint32_t write_val = 0x01;
	uint32_t* read_val = (uint32_t*) malloc(sizeof(uint32_t));
	
	*read_val = 0;

	char* name = "default-fpga";

	//const char* env_name = "AJIT_RESOURCE_FILE";
	
	// char* resource_file = getenv (env_name);

	char resource_file[] = "/sys/bus/pci/devices/0000:0a:00.0/resource0"; 
	
	//fprintf(stderr,"Resource file is :\t %s \n",resource_file);

	void* fpga = initialize_axi_link(name, resource_file);
	
	int write_status = write_to_axi_dram(fpga, address,write_val);

	assert(write_status==0);
	
	fprintf(stderr,"Writing %u at %u in DRAM... \n\n",write_val,address);	

	int read_status = read_from_axi_dram(fpga, address,read_val);
	
	assert(read_status==0);

	fprintf(stderr,"Read %u at %u in DRAM... \n\n",*read_val,address);	

	//fprintf(stderr,"Compare value is %d\n",(*read_val)==write_val);

	assert((*read_val)==write_val);

	return close_axi_link(fpga);
}
