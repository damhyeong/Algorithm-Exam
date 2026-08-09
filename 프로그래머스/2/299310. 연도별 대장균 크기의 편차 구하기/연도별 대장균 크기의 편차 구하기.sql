-- 코드를 작성해주세요
SELECT 
    YEAR(ed.DIFFERENTIATION_DATE) as 'YEAR',
    (ed_max.MAX_SIZE - ed.SIZE_OF_COLONY) as 'YEAR_DEV',
    ed.ID as 'ID'
FROM 
    ECOLI_DATA ed
LEFT JOIN
    (
        SELECT 
            ed2.ID, 
            ed2.DIFFERENTIATION_DATE AS DIFFER_DATE, 
            MAX(ed2.SIZE_OF_COLONY) AS MAX_SIZE
        FROM 
            ECOLI_DATA ed2
        GROUP BY 
            YEAR(ed2.DIFFERENTIATION_DATE)
    ) ed_max ON YEAR(ed_max.DIFFER_DATE) = YEAR(ed.DIFFERENTIATION_DATE)
ORDER BY
    YEAR ASC,
    YEAR_DEV ASC;