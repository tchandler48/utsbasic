USERID UTS
   CLS
   PRINT "Opening Test File"
   OPEN "I", #1, "tests.txt"
Start:
   IF EOF(1) THEN
      GOTO Finish
   ENDIF
   LINE INPUT#1, inp$
Finsh:
   CLOSE 1
TheEnd:
   PRINT "The End"
   END
