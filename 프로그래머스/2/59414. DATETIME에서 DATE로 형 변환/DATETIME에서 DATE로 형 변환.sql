SELECT
    ai.ANIMAL_ID, ai.NAME, (
        DATE_FORMAT(ai.DATETIME, "%Y-%m-%d")
    ) as "날짜"
FROM
    ANIMAL_INS ai;