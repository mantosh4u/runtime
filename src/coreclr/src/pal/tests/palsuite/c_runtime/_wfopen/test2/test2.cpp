// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.

/*=====================================================================
**
** Source:  test2.c
**
** Purpose: Tests the PAL implementation of the _wfopen function. 
**          Test to ensure that you can write to a 'w' mode file.
**          And that you can't read from a 'w' mode file.
**
** Depends:
**      fprintf
**      fseek
**      fgets
**  

**
**===================================================================*/
                
#define UNICODE                                                  
#include <palsuite.h>

PALTEST(c_runtime__wfopen_test2_paltest_wfopen_test2, "c_runtime/_wfopen/test2/paltest_wfopen_test2")
{
  
    FILE *fp;
    char buffer[128];
    WCHAR filename[] = {'t','e','s','t','f','i','l','e','\0'};
    WCHAR write[] = {'w','\0'};

    if (PAL_Initialize(argc, argv))
    {
        return FAIL;
    }

  
    if( (fp = _wfopen( filename, write )) == NULL )
    {
        Fail( "ERROR: The file failed to open with 'w' mode.\n" );
    }  

    /* Test that you can write */
    if(fprintf(fp,"%s","some text") <= 0) 
    {
        Fail("ERROR: Attempted to WRITE to a file opened with 'w' mode "
               "but fprintf failed.  Either fopen or fprintf have problems.");
    }

    if(fseek(fp, 0, SEEK_SET)) 
    {
        Fail("ERROR: fseek failed, and this test depends on it.");
    }

    /* Test that you can't read */
    if(fgets(buffer,10,fp) != NULL)
    {
        Fail("ERROR: Tried to READ from a file with only 'w' mode set. "
               "This should fail, but fgets didn't return NULL.  "
               "Either fgets or fopen is broken.");
    }

    PAL_Terminate();
    return PASS;
}
   

