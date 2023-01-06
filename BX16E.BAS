USERID UTS
'  test16D.bas
   CLS
   PRINT "Opening Test File bx16d.bas"
   OPEN "I", #1, "test.txt"
   OPEN "O", #2, "test2.txt"
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
   WRITE#2, valuea,nxt$,inp$
   GOTO Start
Finish:
   CLOSE 1, 2
TheEnd:
   END

