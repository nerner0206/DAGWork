using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public struct ObjData
{
    public float attack;
    public float speed;
    public float back;
    public float pro;

    public ObjData(float attack, float speed, float back, float pro)
    {
        this.attack = attack;
        this.speed = speed;
        this.back = back;
        this.pro = pro;
    }
};

public class ParamaterManager : MonoBehaviour
{
    //  オブジェクトのデータ
    private static readonly ObjData[] objDatas =
    {
        new ObjData(1.0f,1.0f,1.0f, 1.0f),   //  Cube
        new ObjData(1.0f,1.0f,1.0f, 1.0f),   //  Cylinder
        new ObjData(1.0f,1.0f,1.0f, 1.0f),   //  Sphere
        new ObjData(1.0f,1.0f,1.0f, 1.0f),   //  Cone
        new ObjData(1.0f,1.0f,1.0f, 1.0f),   //  Piramid
        new ObjData(1.0f,1.0f,1.0f, 1.0f),   //  Pipe
    };
    //  最大値
    private static readonly ObjData MAX_STATUS = new ObjData(30.0f, 30.0f, 30.0f, 30.0f);

    //  総合データ
    private ObjData weaponStatus = new ObjData();

    [SerializeField] private List<Image> paraImages;

    private void Start()
    {
        //  初期化
        weaponStatus = new ObjData();

        //  UIの変更
        paraImages[0].fillAmount = (float)weaponStatus.attack / (float)MAX_STATUS.attack;
        paraImages[1].fillAmount = (float)weaponStatus.speed / (float)MAX_STATUS.speed;
        paraImages[2].fillAmount = (float)weaponStatus.back / (float)MAX_STATUS.back;
        paraImages[3].fillAmount = (float)weaponStatus.pro / (float)MAX_STATUS.pro;
    }

    public void MaterUpdate()
    {
        //  パーツを全て探す
        GameObject[] parts = GameObject.FindGameObjectsWithTag("WeaponPart");
        
        //  存在しなれば処理しない
        if (parts == null) return;
        
        //  初期化
        weaponStatus = new ObjData(0.0f, 0.0f, 0.0f, 0.0f);

        //  プレハブをもらう
        List<GameObject> defObjs = gameObject.GetComponent<AddShapeManager>().shapePrefabs;

        //  オブジェクトの数だけ繰り返す
        for (int i = 0; i < parts.Length; i++)
        {
            int num = parts[i].GetComponent<ObjectData>().num;

            weaponStatus.attack += objDatas[num].attack * (parts[i].transform.localScale.x / defObjs[num].transform.localScale.x);
            weaponStatus.speed += objDatas[num].speed * (defObjs[num].transform.localScale.x / parts[i].transform.localScale.x);
            weaponStatus.back += objDatas[num].back * (parts[i].transform.localScale.x / defObjs[num].transform.localScale.x);
            weaponStatus.pro += objDatas[num].pro * (parts[i].transform.localScale.x / defObjs[num].transform.localScale.x);
        }

        if (weaponStatus.attack > MAX_STATUS.attack) weaponStatus.attack = MAX_STATUS.attack;
        if (weaponStatus.speed > MAX_STATUS.speed) weaponStatus.speed = MAX_STATUS.speed;
        if (weaponStatus.back > MAX_STATUS.back) weaponStatus.back = MAX_STATUS.back;
        if (weaponStatus.pro > MAX_STATUS.pro) weaponStatus.pro = MAX_STATUS.pro;

        //  UIの変更
        paraImages[0].fillAmount = weaponStatus.attack / MAX_STATUS.attack;
        paraImages[1].fillAmount = weaponStatus.speed / MAX_STATUS.speed;
        paraImages[2].fillAmount = weaponStatus.back / MAX_STATUS.back;
        paraImages[3].fillAmount = weaponStatus.pro / MAX_STATUS.pro;
    }

    public void DeleteMater()
    {
        GameObject selectObj = gameObject.GetComponent<EditShapeManager>().GetSelectObject();

        int num = selectObj.GetComponent<ObjectData>().num;
        //  プレハブをもらう
        List<GameObject> defObjs = gameObject.GetComponent<AddShapeManager>().shapePrefabs;

        weaponStatus.attack -= objDatas[num].attack * (selectObj.transform.localScale.x / defObjs[num].transform.localScale.x);
        weaponStatus.speed -= objDatas[num].speed * (defObjs[num].transform.localScale.x / selectObj.transform.localScale.x);
        weaponStatus.back -= objDatas[num].back * (selectObj.transform.localScale.x / defObjs[num].transform.localScale.x);
        weaponStatus.pro -= objDatas[num].pro * (selectObj.transform.localScale.x / defObjs[num].transform.localScale.x);

        //  UIの変更
        paraImages[0].fillAmount = weaponStatus.attack / MAX_STATUS.attack;
        paraImages[1].fillAmount = weaponStatus.speed / MAX_STATUS.speed;
        paraImages[2].fillAmount = weaponStatus.back / MAX_STATUS.back;
        paraImages[3].fillAmount = weaponStatus.pro / MAX_STATUS.pro;
    }
}
