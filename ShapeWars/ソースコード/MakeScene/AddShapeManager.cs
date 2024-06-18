using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.IO;

public class Weapon
{
    public int animID;
    public int[] ID;
    public Vector3[] pos;
    public Vector3[] rot;
    public Vector3[] sca;
}

public class AddShapeManager : MonoBehaviour
{
    //  親のハンドルオブジェクト
    [SerializeField] private GameObject handleObject;
    [SerializeField] private GameObject handlePrefab;

    //  追加するオブジェクト
    public List<GameObject> shapePrefabs;

    //  セーブ用のクラス変数
    Weapon weapon = new Weapon();

    //  図形を生成する
    public GameObject AddShape(int num)
    {
        //  生成する
        GameObject part = Instantiate(shapePrefabs[num], Vector3.zero, Quaternion.identity);
        //  子オブジェクトにする
        part.transform.parent = handleObject.transform;
        //  図形番号を入れる
        part.GetComponent<ObjectData>().num = num;

        return part;
    }

    //  セーブする
    public void Save(int num, int animNum)
    {
        //  クラスに格納する
        //  部品を格納(ここの処理は重い)
        GameObject[] weaponParts = GameObject.FindGameObjectsWithTag("WeaponPart");

        //  クラスを初期化
        weapon = new Weapon();
        //  アニメーション番号
        weapon.animID = animNum;

        //  見つけたオブジェクトの番号を取得
        if(weaponParts != null)
        {
            weapon.ID = new int[weaponParts.Length];
            weapon.pos = new Vector3[weaponParts.Length];
            weapon.rot = new Vector3[weaponParts.Length];
            weapon.sca = new Vector3[weaponParts.Length];

            for (int i = 0; i < weaponParts.Length; i++)
            {
                weapon.ID[i] = weaponParts[i].GetComponent<ObjectData>().num;
                weapon.pos[i] = weaponParts[i].transform.position;
                weapon.rot[i] = weaponParts[i].transform.eulerAngles;
                weapon.sca[i] = weaponParts[i].transform.localScale;
            }

        }

        // ToJsonメソッドの第２引数は、見やすくフォーマットするスイッチです
        string jsonString = JsonUtility.ToJson(weapon, true);
        // JSONデータをファイルに保存
        File.WriteAllText(Initialize.dataPathes[num], jsonString);
    }
}
