SELECT 
    ai.ANIMAL_ID,
    ai.NAME,
    ai.SEX_UPON_INTAKE
FROM 
    ANIMAL_INS ai
WHERE
    ai.NAME
    IN ('Lucy', 'Ella', 'Pickle', 'Rogan', 'Sabrina', 'Mitty')
ORDER BY
    ai.ANIMAL_ID ASC;