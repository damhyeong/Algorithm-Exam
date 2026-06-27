SELECT
    ugb.BOARD_ID, ugb.WRITER_ID, ugb.TITLE, ugb.PRICE, 
    CASE 
        WHEN ugb.STATUS = 'RESERVED' THEN '예약중'
        WHEN ugb.STATUS = 'SALE' THEN '판매중'
        ELSE '거래완료' 
    END AS 'STATUS'
FROM
    USED_GOODS_BOARD ugb
WHERE
    ugb.CREATED_DATE = '2022-10-05'
ORDER BY
    ugb.BOARD_ID DESC;