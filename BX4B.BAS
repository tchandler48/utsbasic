USERID UTS
   REM BX4B.BAS
   CLS
   GOTO OverThere
TheBeginning:
   PRINT "We are at the beginning"
   GOTO TheEnd
There:
   PRINT "We are There"
   GOTO TheBeginning
JumpBack1:
   PRINT "We are at Jumpback1"
   GOTO There
OverThere:
   PRINT "We are at OverThere"
   GOTO JumpBack1
TheEnd:
   END
