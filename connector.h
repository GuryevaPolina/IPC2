//
//  connector.h
//  lab2
//
//  Created by Polina Guryeva on 01/12/2018.
//  Copyright © 2018 Polina Guryeva. All rights reserved.
//

#pragma once
#ifndef connector_h
#define connector_h
#define TRUE 1
#define FALSE 0

void create_connection(void);
void destroy_connection(void);

void read_data(void* data, size_t size);
void write_data(void* data, size_t size);

#endif /* connector_h */
