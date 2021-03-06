(set-logic HORN)
(define-fun
   IN_INV
   ((i$1_0 Int)
    (j$1_0 Int)
    (i$2_0 Int)
    (j$2_0 Int))
   Bool
   (and
      (= i$1_0 i$2_0)
      (= j$1_0 j$2_0)))
(define-fun
   OUT_INV
   ((result$1 Int)
    (result$2 Int))
   Bool
   (= result$1 result$2))
(declare-fun
   INV_REC_f
   (Int
    Int
    Int
    Int
    Int
    Int)
   Bool)
(declare-fun
   INV_REC_f_PRE
   (Int
    Int
    Int
    Int)
   Bool)
(declare-fun
   INV_REC_f__1
   (Int
    Int
    Int)
   Bool)
(declare-fun
   INV_REC_f__1_PRE
   (Int
    Int)
   Bool)
(declare-fun
   INV_REC_f__2
   (Int
    Int
    Int)
   Bool)
(declare-fun
   INV_REC_f__2_PRE
   (Int
    Int)
   Bool)
(assert
   (forall
      ((i$1_0_old Int)
       (j$1_0_old Int)
       (i$2_0_old Int)
       (j$2_0_old Int))
      (=>
         (IN_INV
            i$1_0_old
            j$1_0_old
            i$2_0_old
            j$2_0_old)
         (let
            ((_$1_0 (= i$1_0_old 0)))
            (=>
               _$1_0
               (let
                  ((r.0$1_0 j$1_0_old))
                  (let
                     ((result$1 r.0$1_0)
                      (i$1_0 i$1_0_old)
                      (j$1_0 j$1_0_old)
                      (_$2_0 (= i$2_0_old 0)))
                     (=>
                        _$2_0
                        (let
                           ((r.1$2_0 j$2_0_old))
                           (let
                              ((result$2 r.1$2_0)
                               (i$2_0 i$2_0_old)
                               (j$2_0 j$2_0_old))
                              (OUT_INV
                                 result$1
                                 result$2)))))))))))
(assert
   (forall
      ((i$1_0_old Int)
       (j$1_0_old Int)
       (i$2_0_old Int)
       (j$2_0_old Int))
      (=>
         (IN_INV
            i$1_0_old
            j$1_0_old
            i$2_0_old
            j$2_0_old)
         (let
            ((_$1_0 (= i$1_0_old 0)))
            (=>
               _$1_0
               (let
                  ((r.0$1_0 j$1_0_old))
                  (let
                     ((result$1 r.0$1_0)
                      (i$1_0 i$1_0_old)
                      (j$1_0 j$1_0_old)
                      (_$2_0 (= i$2_0_old 0)))
                     (=>
                        (not _$2_0)
                        (let
                           ((_$2_1 (= i$2_0_old 1)))
                           (=>
                              _$2_1
                              (let
                                 ((_$2_2 (+ j$2_0_old 1)))
                                 (let
                                    ((r.0$2_0 _$2_2))
                                    (let
                                       ((r.1$2_0 r.0$2_0))
                                       (let
                                          ((result$2 r.1$2_0)
                                           (i$2_0 i$2_0_old)
                                           (j$2_0 j$2_0_old))
                                          (OUT_INV
                                             result$1
                                             result$2)))))))))))))))
(assert
 (forall
  ((i$1_0_old Int)
   (j$1_0_old Int)
   (i$2_0_old Int)
   (j$2_0_old Int))
  (=>
   (IN_INV
    i$1_0_old
    j$1_0_old
    i$2_0_old
    j$2_0_old)
   (let
       ((_$2_0 (= i$2_0_old 0)))
     (=>
      (not _$2_0)
      (let
          ((_$2_1 (= i$2_0_old 1)))
        (=>
         (not _$2_1)
         (let
             ((_$2_3 (- i$2_0_old 1))
              (_$2_4 (+ j$2_0_old 1)))
           (and
            (INV_REC_f__2_PRE _$2_3 _$2_4)
            (forall
             ((_$2_5 Int))
             (=>
              (INV_REC_f__2 _$2_3 _$2_4 _$2_5)
              (let
                  ((_$1_0 (= i$1_0_old 0)))
                (=>
                 _$1_0
                 (let
                     ((r.0$1_0 j$1_0_old))
                   (let
                       ((result$1 r.0$1_0)
                        (i$1_0 i$1_0_old)
                        (j$1_0 j$1_0_old)
                        (r.0$2_0 _$2_5))
                     (let
                         ((r.1$2_0 r.0$2_0))
                       (let
                           ((result$2 r.1$2_0)
                            (i$2_0 i$2_0_old)
                            (j$2_0 j$2_0_old))
                         (OUT_INV
                          result$1
                          result$2))))))))))))))))))
(assert
 (forall
  ((i$1_0_old Int)
   (j$1_0_old Int)
   (i$2_0_old Int)
   (j$2_0_old Int))
  (=>
   (IN_INV
    i$1_0_old
    j$1_0_old
    i$2_0_old
    j$2_0_old)
   (let
       ((_$1_0 (= i$1_0_old 0)))
     (=>
      (not _$1_0)
      (let
          ((_$1_1 (- i$1_0_old 1))
           (_$1_2 (+ j$1_0_old 1)))
        (let
            ((_$2_0 (= i$2_0_old 0)))
          (=>
           _$2_0
           (let
               ((r.1$2_0 j$2_0_old))
             (let
                 ((result$2 r.1$2_0)
                  (i$2_0 i$2_0_old)
                  (j$2_0 j$2_0_old))
               (and
                (INV_REC_f__1_PRE _$1_1 _$1_2)
                (forall
                 ((_$1_3 Int))
                 (=>
                  (INV_REC_f__1 _$1_1 _$1_2 _$1_3)
                  (let
                      ((r.0$1_0 _$1_3))
                    (let
                        ((result$1 r.0$1_0)
                         (i$1_0 i$1_0_old)
                         (j$1_0 j$1_0_old))
                      (OUT_INV
                       result$1
                       result$2))))))))))))))))
(assert
 (forall
  ((i$1_0_old Int)
   (j$1_0_old Int)
   (i$2_0_old Int)
   (j$2_0_old Int))
  (=>
   (IN_INV
    i$1_0_old
    j$1_0_old
    i$2_0_old
    j$2_0_old)
   (let
       ((_$1_0 (= i$1_0_old 0)))
     (=>
      (not _$1_0)
      (let
          ((_$1_1 (- i$1_0_old 1))
           (_$1_2 (+ j$1_0_old 1))
           (_$2_0 (= i$2_0_old 0)))
        (=>
         (not _$2_0)
         (let
             ((_$2_1 (= i$2_0_old 1)))
           (=>
            _$2_1
            (let
                ((_$2_2 (+ j$2_0_old 1)))
              (let
                  ((r.0$2_0 _$2_2))
                (let
                    ((r.1$2_0 r.0$2_0))
                  (let
                      ((result$2 r.1$2_0)
                       (i$2_0 i$2_0_old)
                       (j$2_0 j$2_0_old))
                    (and
                     (INV_REC_f__1_PRE _$1_1 _$1_2)
                     (forall
                      ((_$1_3 Int))
                      (=>
                       (INV_REC_f__1 _$1_1 _$1_2 _$1_3)
                       (let
                           ((r.0$1_0 _$1_3))
                         (let
                             ((result$1 r.0$1_0)
                              (i$1_0 i$1_0_old)
                              (j$1_0 j$1_0_old))
                           (OUT_INV
                            result$1
                            result$2)))))))))))))))))))
(assert
   (forall
      ((i$1_0_old Int)
       (j$1_0_old Int)
       (i$2_0_old Int)
       (j$2_0_old Int))
      (=>
         (IN_INV
            i$1_0_old
            j$1_0_old
            i$2_0_old
            j$2_0_old)
         (let
            ((_$1_0 (= i$1_0_old 0)))
            (=>
               (not _$1_0)
               (let
                  ((_$1_1 (- i$1_0_old 1))
                   (_$1_2 (+ j$1_0_old 1))
                   (_$2_0 (= i$2_0_old 0)))
                  (=>
                     (not _$2_0)
                     (let
                        ((_$2_1 (= i$2_0_old 1)))
                        (=>
                           (not _$2_1)
                           (let
                              ((_$2_3 (- i$2_0_old 1))
                               (_$2_4 (+ j$2_0_old 1)))
                              (and
                                 (INV_REC_f_PRE _$1_1 _$1_2 _$2_3 _$2_4)
                                 (forall
                                    ((_$1_3 Int)
                                     (_$2_5 Int))
                                    (=>
                                       (INV_REC_f _$1_1 _$1_2 _$2_3 _$2_4 _$1_3 _$2_5)
                                       (let
                                          ((r.0$1_0 _$1_3))
                                          (let
                                             ((result$1 r.0$1_0)
                                              (i$1_0 i$1_0_old)
                                              (j$1_0 j$1_0_old)
                                              (r.0$2_0 _$2_5))
                                             (let
                                                ((r.1$2_0 r.0$2_0))
                                                (let
                                                   ((result$2 r.1$2_0)
                                                    (i$2_0 i$2_0_old)
                                                    (j$2_0 j$2_0_old))
                                                   (OUT_INV
                                                      result$1
                                                      result$2))))))))))))))))))
; forbidden main
; offbyn main
; end
(assert
   (forall
      ((i$1_0_old Int)
       (j$1_0_old Int)
       (i$2_0_old Int)
       (j$2_0_old Int))
      (=>
         (INV_REC_f_PRE i$1_0_old j$1_0_old i$2_0_old j$2_0_old)
         (let
            ((_$1_0 (= i$1_0_old 0)))
            (=>
               _$1_0
               (let
                  ((r.0$1_0 j$1_0_old))
                  (let
                     ((result$1 r.0$1_0)
                      (i$1_0 i$1_0_old)
                      (j$1_0 j$1_0_old)
                      (_$2_0 (= i$2_0_old 0)))
                     (=>
                        _$2_0
                        (let
                           ((r.1$2_0 j$2_0_old))
                           (let
                              ((result$2 r.1$2_0)
                               (i$2_0 i$2_0_old)
                               (j$2_0 j$2_0_old))
                              (INV_REC_f i$1_0_old j$1_0_old i$2_0_old j$2_0_old result$1 result$2)))))))))))
(assert
   (forall
      ((i$1_0_old Int)
       (j$1_0_old Int)
       (i$2_0_old Int)
       (j$2_0_old Int))
      (=>
         (INV_REC_f_PRE i$1_0_old j$1_0_old i$2_0_old j$2_0_old)
         (let
            ((_$1_0 (= i$1_0_old 0)))
            (=>
               _$1_0
               (let
                  ((r.0$1_0 j$1_0_old))
                  (let
                     ((result$1 r.0$1_0)
                      (i$1_0 i$1_0_old)
                      (j$1_0 j$1_0_old)
                      (_$2_0 (= i$2_0_old 0)))
                     (=>
                        (not _$2_0)
                        (let
                           ((_$2_1 (= i$2_0_old 1)))
                           (=>
                              _$2_1
                              (let
                                 ((_$2_2 (+ j$2_0_old 1)))
                                 (let
                                    ((r.0$2_0 _$2_2))
                                    (let
                                       ((r.1$2_0 r.0$2_0))
                                       (let
                                          ((result$2 r.1$2_0)
                                           (i$2_0 i$2_0_old)
                                           (j$2_0 j$2_0_old))
                                          (INV_REC_f i$1_0_old j$1_0_old i$2_0_old j$2_0_old result$1 result$2)))))))))))))))
(assert
 (forall
  ((i$1_0_old Int)
   (j$1_0_old Int)
   (i$2_0_old Int)
   (j$2_0_old Int))
  (=>
   (INV_REC_f_PRE i$1_0_old j$1_0_old i$2_0_old j$2_0_old)
   (let
       ((_$2_0 (= i$2_0_old 0)))
     (=>
      (not _$2_0)
      (let
          ((_$2_1 (= i$2_0_old 1)))
        (=>
         (not _$2_1)
         (let
             ((_$2_3 (- i$2_0_old 1))
              (_$2_4 (+ j$2_0_old 1)))
           (and
            (INV_REC_f__2_PRE _$2_3 _$2_4)
            (forall
             ((_$2_5 Int))
             (=>
              (INV_REC_f__2 _$2_3 _$2_4 _$2_5)
              (let
                  ((_$1_0 (= i$1_0_old 0)))
                (=>
                 _$1_0
                 (let
                     ((r.0$1_0 j$1_0_old))
                   (let
                       ((result$1 r.0$1_0)
                        (i$1_0 i$1_0_old)
                        (j$1_0 j$1_0_old)
                        (r.0$2_0 _$2_5))
                     (let
                         ((r.1$2_0 r.0$2_0))
                       (let
                           ((result$2 r.1$2_0)
                            (i$2_0 i$2_0_old)
                            (j$2_0 j$2_0_old))
                         (INV_REC_f i$1_0_old j$1_0_old i$2_0_old j$2_0_old result$1 result$2))))))))))))))))))
(assert
 (forall
  ((i$1_0_old Int)
   (j$1_0_old Int)
   (i$2_0_old Int)
   (j$2_0_old Int))
  (=>
   (INV_REC_f_PRE i$1_0_old j$1_0_old i$2_0_old j$2_0_old)
   (let
       ((_$1_0 (= i$1_0_old 0)))
     (=>
      (not _$1_0)
      (let
          ((_$1_1 (- i$1_0_old 1))
           (_$1_2 (+ j$1_0_old 1))
           (_$2_0 (= i$2_0_old 0)))
        (=>
         _$2_0
         (let
             ((r.1$2_0 j$2_0_old))
           (let
               ((result$2 r.1$2_0)
                (i$2_0 i$2_0_old)
                (j$2_0 j$2_0_old))
             (and
              (INV_REC_f__1_PRE _$1_1 _$1_2)
              (forall
               ((_$1_3 Int))
               (=>
                (INV_REC_f__1 _$1_1 _$1_2 _$1_3)
                (let
                    ((r.0$1_0 _$1_3))
                  (let
                      ((result$1 r.0$1_0)
                       (i$1_0 i$1_0_old)
                       (j$1_0 j$1_0_old))
                    (INV_REC_f i$1_0_old j$1_0_old i$2_0_old j$2_0_old result$1 result$2)))))))))))))))
(assert
 (forall
  ((i$1_0_old Int)
   (j$1_0_old Int)
   (i$2_0_old Int)
   (j$2_0_old Int))
  (=>
   (INV_REC_f_PRE i$1_0_old j$1_0_old i$2_0_old j$2_0_old)
   (let
       ((_$1_0 (= i$1_0_old 0)))
     (=>
      (not _$1_0)
      (let
          ((_$1_1 (- i$1_0_old 1))
           (_$1_2 (+ j$1_0_old 1))
           (_$2_0 (= i$2_0_old 0)))
        (=>
         (not _$2_0)
         (let
             ((_$2_1 (= i$2_0_old 1)))
           (=>
            _$2_1
            (let
                ((_$2_2 (+ j$2_0_old 1)))
              (let
                  ((r.0$2_0 _$2_2))
                (let
                    ((r.1$2_0 r.0$2_0))
                  (let
                      ((result$2 r.1$2_0)
                       (i$2_0 i$2_0_old)
                       (j$2_0 j$2_0_old))
                    (and
                     (INV_REC_f__1_PRE _$1_1 _$1_2)
                     (forall
                      ((_$1_3 Int))
                      (=>
                       (INV_REC_f__1 _$1_1 _$1_2 _$1_3)
                       (let
                           ((r.0$1_0 _$1_3))
                         (let
                             ((result$1 r.0$1_0)
                              (i$1_0 i$1_0_old)
                              (j$1_0 j$1_0_old))
                           (INV_REC_f i$1_0_old j$1_0_old i$2_0_old j$2_0_old result$1 result$2)))))))))))))))))))
(assert
   (forall
      ((i$1_0_old Int)
       (j$1_0_old Int)
       (i$2_0_old Int)
       (j$2_0_old Int))
      (=>
         (INV_REC_f_PRE i$1_0_old j$1_0_old i$2_0_old j$2_0_old)
         (let
            ((_$1_0 (= i$1_0_old 0)))
            (=>
               (not _$1_0)
               (let
                  ((_$1_1 (- i$1_0_old 1))
                   (_$1_2 (+ j$1_0_old 1))
                   (_$2_0 (= i$2_0_old 0)))
                  (=>
                     (not _$2_0)
                     (let
                        ((_$2_1 (= i$2_0_old 1)))
                        (=>
                           (not _$2_1)
                           (let
                              ((_$2_3 (- i$2_0_old 1))
                               (_$2_4 (+ j$2_0_old 1)))
                              (and
                                 (INV_REC_f_PRE _$1_1 _$1_2 _$2_3 _$2_4)
                                 (forall
                                    ((_$1_3 Int)
                                     (_$2_5 Int))
                                    (=>
                                       (INV_REC_f _$1_1 _$1_2 _$2_3 _$2_4 _$1_3 _$2_5)
                                       (let
                                          ((r.0$1_0 _$1_3))
                                          (let
                                             ((result$1 r.0$1_0)
                                              (i$1_0 i$1_0_old)
                                              (j$1_0 j$1_0_old)
                                              (r.0$2_0 _$2_5))
                                             (let
                                                ((r.1$2_0 r.0$2_0))
                                                (let
                                                   ((result$2 r.1$2_0)
                                                    (i$2_0 i$2_0_old)
                                                    (j$2_0 j$2_0_old))
                                                   (INV_REC_f i$1_0_old j$1_0_old i$2_0_old j$2_0_old result$1 result$2))))))))))))))))))
(assert
   (forall
      ((i$1_0_old Int)
       (j$1_0_old Int))
      (=>
         (INV_REC_f__1_PRE i$1_0_old j$1_0_old)
         (let
            ((_$1_0 (= i$1_0_old 0)))
            (=>
               _$1_0
               (let
                  ((r.0$1_0 j$1_0_old))
                  (let
                     ((result$1 r.0$1_0)
                      (i$1_0 i$1_0_old)
                      (j$1_0 j$1_0_old))
                     (INV_REC_f__1 i$1_0_old j$1_0_old result$1))))))))
(assert
   (forall
      ((i$1_0_old Int)
       (j$1_0_old Int))
      (=>
         (INV_REC_f__1_PRE i$1_0_old j$1_0_old)
         (let
            ((_$1_0 (= i$1_0_old 0)))
            (=>
               (not _$1_0)
               (let
                  ((_$1_1 (- i$1_0_old 1))
                   (_$1_2 (+ j$1_0_old 1)))
                  (and
                     (INV_REC_f__1_PRE _$1_1 _$1_2)
                     (forall
                        ((_$1_3 Int))
                        (=>
                           (INV_REC_f__1 _$1_1 _$1_2 _$1_3)
                           (let
                              ((r.0$1_0 _$1_3))
                              (let
                                 ((result$1 r.0$1_0)
                                  (i$1_0 i$1_0_old)
                                  (j$1_0 j$1_0_old))
                                 (INV_REC_f__1 i$1_0_old j$1_0_old result$1))))))))))))
(assert
   (forall
      ((i$2_0_old Int)
       (j$2_0_old Int))
      (=>
         (INV_REC_f__2_PRE i$2_0_old j$2_0_old)
         (let
            ((_$2_0 (= i$2_0_old 0)))
            (=>
               _$2_0
               (let
                  ((r.1$2_0 j$2_0_old))
                  (let
                     ((result$2 r.1$2_0)
                      (i$2_0 i$2_0_old)
                      (j$2_0 j$2_0_old))
                     (INV_REC_f__2 i$2_0_old j$2_0_old result$2))))))))
(assert
   (forall
      ((i$2_0_old Int)
       (j$2_0_old Int))
      (=>
         (INV_REC_f__2_PRE i$2_0_old j$2_0_old)
         (let
            ((_$2_0 (= i$2_0_old 0)))
            (=>
               (not _$2_0)
               (let
                  ((_$2_1 (= i$2_0_old 1)))
                  (=>
                     _$2_1
                     (let
                        ((_$2_2 (+ j$2_0_old 1)))
                        (let
                           ((r.0$2_0 _$2_2))
                           (let
                              ((r.1$2_0 r.0$2_0))
                              (let
                                 ((result$2 r.1$2_0)
                                  (i$2_0 i$2_0_old)
                                  (j$2_0 j$2_0_old))
                                 (INV_REC_f__2 i$2_0_old j$2_0_old result$2))))))))))))
(assert
   (forall
      ((i$2_0_old Int)
       (j$2_0_old Int))
      (=>
         (INV_REC_f__2_PRE i$2_0_old j$2_0_old)
         (let
            ((_$2_0 (= i$2_0_old 0)))
            (=>
               (not _$2_0)
               (let
                  ((_$2_1 (= i$2_0_old 1)))
                  (=>
                     (not _$2_1)
                     (let
                        ((_$2_3 (- i$2_0_old 1))
                         (_$2_4 (+ j$2_0_old 1)))
                        (and
                           (INV_REC_f__2_PRE _$2_3 _$2_4)
                           (forall
                              ((_$2_5 Int))
                              (=>
                                 (INV_REC_f__2 _$2_3 _$2_4 _$2_5)
                                 (let
                                    ((r.0$2_0 _$2_5))
                                    (let
                                       ((r.1$2_0 r.0$2_0))
                                       (let
                                          ((result$2 r.1$2_0)
                                           (i$2_0 i$2_0_old)
                                           (j$2_0 j$2_0_old))
                                          (INV_REC_f__2 i$2_0_old j$2_0_old result$2)))))))))))))))
; FORBIDDEN PATHS
; OFF BY N
(check-sat)
(get-model)
