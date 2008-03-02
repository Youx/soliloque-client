//
//  main.m
//  Freespeak
//
//  Created by Hugo Camboulive on 01/03/08.
//  Copyright __MyCompanyName__ 2008. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "FreespeakController.h"

FreespeakController * fscont;

/*void addLineToLogger(char * line) {
  [NSApp addLog:[NSString stringWithCString:line]];
}*/

void *thread_func( void *vptr_args ){
  main2();
  //  sleep(2);
  return NULL;
}

int main(int argc, char *argv[])
{
  //fscont = [[FreespeakController alloc] init];
  pthread_t thread;
  pthread_create(&thread, NULL, thread_func, NULL);
  
  return NSApplicationMain(argc,  (const char **) argv);
}


