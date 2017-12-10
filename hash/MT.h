//
//  MT.h
//  hash
//
//  Created by 津田準 on 2017/12/10.
//  Copyright © 2017 津田準. All rights reserved.
//

#ifndef MT_h
#define MT_h

void init_genrand(unsigned long s);
void init_by_array(unsigned long init_key[], int key_length);
unsigned long genrand_int32(void);
long genrand_int31(void);


#endif /* MT_h */
