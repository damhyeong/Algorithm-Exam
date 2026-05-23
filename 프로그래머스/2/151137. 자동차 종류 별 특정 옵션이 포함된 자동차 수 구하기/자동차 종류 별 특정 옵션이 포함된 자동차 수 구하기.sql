SELECT
    crcc.CAR_TYPE, COUNT(CAR_TYPE)
FROM
    CAR_RENTAL_COMPANY_CAR crcc
WHERE
    crcc.OPTIONS LIKE "%통풍시트%"
    OR crcc.OPTIONS LIKE "%열선시트%"
    OR crcc.OPTIONS LIKE "%가죽시트%"
GROUP BY
    crcc.CAR_TYPE    
ORDER BY
    crcc.CAR_TYPE ASC;