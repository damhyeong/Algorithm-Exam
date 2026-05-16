SELECT
    COUNT(ed1.ID)
FROM
    ECOLI_DATA ed1
WHERE
    (
        SELECT
            ed2.ID
        FROM
            ECOLI_DATA ed2
        WHERE
            ((ed2.GENOTYPE % 2) = 1 OR ((ed2.GENOTYPE >> 2) % 2) = 1)
            AND ((ed2.GENOTYPE >> 1) % 2) = 0
            AND ed1.ID = ed2.ID
    );