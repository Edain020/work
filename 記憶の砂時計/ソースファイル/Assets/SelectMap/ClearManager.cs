using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class ClearManager
{
    static int clearNum = -1;

    public static void Add()
    {
        clearNum++;
        DataSave();
    }

    public static int getClearNum()
    {
        if (clearNum == -1)
            DataLoad();

        return clearNum;
    }

    private static void DataLoad()
    {
        if (!PlayerPrefs.HasKey("Data"))
            PlayerPrefs.SetInt("Data", 0);

        clearNum = PlayerPrefs.GetInt("Data");
    }

    private static void DataSave()
    {
        PlayerPrefs.SetInt("Data", clearNum);
        PlayerPrefs.Save();
    }
}
