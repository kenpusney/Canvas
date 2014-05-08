/* 
 * File:   certainly.h
 * Author: liuqing
 *
 * Created on 2014年5月8日, 上午10:29
 */

#ifndef CERTAINLY_H
#define	CERTAINLY_H
 
#define repeat do
#define until(exp) while(!(exp))
 
#define unless(exp) if(!(exp))
 
#define redo contiune
#define last break
#define jump goto
 
#define cond if(0){}
#define when else if
#define elsif else if
#define except else

#define match switch

#endif	/* CERTAINLY_H */

