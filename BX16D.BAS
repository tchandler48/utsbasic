USERID UTS
'  test16D.bas
   CLS
   PRINT "Opening Test File bx16d.bas"
   OPEN "I", #1, "test.txt"
Start:
   IF EOF(1) THEN
      GOTO Finish
   ENDIF
   INPUT#1,inp$,nxt$,valuea
   IF inp$ = "" THEN
      GOTO Start
   ENDIF
   PRINT inp$
   PRINT nxt$
   PRINT valuea
   GOTO Start
Finish:
   CLOSE 1
TheEnd:
   END
