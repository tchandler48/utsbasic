USERID UTS
   CLS
   GOSUB Start1
   GOSUB DoubleFloat
   GOSUB LongIntegers
   GOSUB RDParser
   GOSUB PrintVars
   GOTO TheEnd
Start1:
   Hello$ = "hello World"
   PRINT Hello$
   RETURN
DoubleFloat:
   PRINT "Inside DoubleFloat"
   RETURN
LongIntegers:
   PRINT "Inside LongIntegers"
   RETURN
RDParser:
   PRINT "Inside RDParser"
   RETURN
PrintVars:
   PRINT "Inside PrintVars"
   RETURN
TheEnd:
   END
