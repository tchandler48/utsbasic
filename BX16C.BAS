USERID UTS
'  test16c.bas
   CLS
   PRINT "Opening Test File bx16c.bas"
   OPEN "I", #1, "test.txt"
   INPUT#1,inp$,nxt$,valuea
   CLOSE 1
   PRINT inp$
   PRINT nxt$
   PRINT valuea
TheEnd:
   END
