using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.IO;

public class Initialize
{
    // ファイルパス
    public static string[] dataPathes = new string[6];

    [RuntimeInitializeOnLoadMethod(RuntimeInitializeLoadType.BeforeSceneLoad)]
    public static void InitializeApplication()
    {
        //  データパスを設定する
        dataPathes[0] = Path.Combine(Application.persistentDataPath, "Weapon01.json");
        dataPathes[1] = Path.Combine(Application.persistentDataPath, "Weapon02.json");
        dataPathes[2] = Path.Combine(Application.persistentDataPath, "Weapon03.json");
        dataPathes[3] = Path.Combine(Application.persistentDataPath, "Weapon04.json");
        dataPathes[4] = Path.Combine(Application.persistentDataPath, "Weapon05.json");
        dataPathes[5] = Path.Combine(Application.persistentDataPath, "Weapon06.json");
    }
}
