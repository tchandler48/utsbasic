USERID UTS
   REM  BX10B.BAS
   CLS
   xyz$ = "testing"
   abc$ = LEFT$(xyz$,4)
   PRINT abc$
   REM
   abc$ = RIGHT$(xyz$, 5)
   PRINT abc$
   abc$ = MID$(xyz$,3,3)
   PRINT abc$
   END
