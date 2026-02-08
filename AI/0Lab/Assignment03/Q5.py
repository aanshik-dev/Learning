import pandas as pd

time_df = pd.DataFrame({
    "TimeStamp": [
        "2025-02-02 14:35:00",
        "2025-02-02 09:10:00",
        "2025-02-02 23:59:00"
    ]
})

time_df["TimeStamp"] = pd.to_datetime(time_df["TimeStamp"])

time_df["Hour"] = time_df["TimeStamp"].dt.hour
print(time_df)
