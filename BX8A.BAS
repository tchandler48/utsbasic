USERID UTS
   REM BX8A.BAS
   abc = 99
   xyz = 33
   abc$ = "test"
   xyz$ = "testing"
   REM
   IF xyz$ = "testing" AND abc >= xyz THEN
      PRINT "if:expression = true"
   ELSEIF abc <= 100 OR abc$ <= "hello" THEN
      PRINT "elseif:expression = true"
   ELSE
      PRINT "else:expressions = false"
   ENDIF
   PRINT "done"
TheEnd:
   END
