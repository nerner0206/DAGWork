using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

public class EditShapeManager : MonoBehaviour
{
    //  ゲームパッド
    private Gamepad gamepad;

    //  選択しているオブジェクトの設定
    private GameObject selectObject;

    //  デッドゾーン
    [SerializeField] private float DEAD_ZONE = 0.1f;

    //  移動速度
    [SerializeField] private float MOVE_SPEED = 1.0f;
    //  回転速度
    [SerializeField] private float ROT_SPEED = 1.0f;
    //  拡大速度
    [SerializeField] private float SCA_SPEED = 1.0f;

    private Vector3 objScreenPos;

    //  デフォルト
    private Vector3 defPos;
    private Vector3 defRot;
    private Vector3 defSca;

    //  マテリアル
    [SerializeField] private Material def;
    [SerializeField] private Material line;

    //  選択したオブジェクトを設定
    public void SetSelectObject(GameObject select)
    {
        //  オブジェクトを渡す
        selectObject = select;
        //  マテリアルの変更
        selectObject.GetComponent<MeshRenderer>().material = line;

        defPos = selectObject.transform.position;
        defRot = selectObject.transform.eulerAngles;
        defSca = selectObject.transform.localScale;
    }
    public GameObject GetSelectObject()
    {
        return selectObject;
    }
    //  選択したオブジェクトを外す
    public void ResetSelectObject()
    {
        //  マテリアルの変更
        selectObject.GetComponent<MeshRenderer>().material = def;
        //  オブジェクトを外す
        selectObject = null;
    }
    //  レイを飛ばす
    public bool FlyingRay(Vector3 iconPos, Vector3 camPos)
    {
        //  レイを飛ばす方向を決める(x,z座標上)
        Vector3 dec = (-2.0f * new Vector3(camPos.x, 0.0f, camPos.z)).normalized;
        //  最初の座標
        Vector3 start = Camera.main.ScreenToWorldPoint(iconPos);

        //  当たり判定を取るレイを生成
        RaycastHit hit = new RaycastHit();
        //  球のレイを飛ばして接触しているか判定する
        Ray ray = new Ray(start, dec);

        if (Physics.SphereCast(ray, 0.5f, out hit, 100f, LayerMask.GetMask("Target")))
        {
            //  当たったオブジェクトを選択状態にする
            SetSelectObject(hit.transform.gameObject);
            return true;
        }

        return false;
    }

    //  図形の編集更新処理
    public void EditShapeUpdate()
    {
        //  ゲームパッド取得
        gamepad = Gamepad.current;
        if (gamepad == null) return;

        //  選択オブジェクトが無ければ処理しない
        if (selectObject == null) return;

        //  移動
        ShapeMove();
        //  回転
        ShapeRot();
        //  拡大
        ShapeScale();
    }
    //  図形を削除
    public void DeleteShape()
    {
        //  削除する
        Destroy(selectObject);

        selectObject = null;
    }
    public Vector3 GetObjScreenPos()
    {
        return objScreenPos;
    }

    //  移動
    private void ShapeMove()
    {
        //  入力を受け取る
        Vector2 input = gamepad.leftStick.ReadValue();
        //  入力が小さい場合処理しない
        if (Mathf.Abs(input.x) < DEAD_ZONE && Mathf.Abs(input.y) < DEAD_ZONE) return;

        //  オブジェクトのスクリーン座標を取得
        objScreenPos = Camera.main.WorldToScreenPoint(selectObject.transform.position);
        //  入力に応じて座標をずらす
        objScreenPos += new Vector3(input.x * Time.deltaTime * MOVE_SPEED, input.y * Time.deltaTime * MOVE_SPEED, 0.0f);

        Debug.Log(objScreenPos);

        //  移動範囲から飛び出したら修正する
        if (objScreenPos.y < 105) objScreenPos.y = 105;
        else if (objScreenPos.y > 760.0f) objScreenPos.y = 760.0f;
        if (objScreenPos.x < Screen.width / 2.0f - 576.0f) objScreenPos.x = Screen.width / 2.0f - 576.0f;
        if (objScreenPos.x > Screen.width / 2.0f + 576.0f) objScreenPos.x = Screen.width / 2.0f + 576.0f;

        //  座標を入れる
        selectObject.transform.position = Camera.main.ScreenToWorldPoint(objScreenPos);
    }
    //  回転
    private void ShapeRot()
    {
        //  入力を受け取る
        Vector2 input = gamepad.rightStick.ReadValue();
        //  入力が小さい場合処理しない
        if (Mathf.Abs(input.x) < DEAD_ZONE && Mathf.Abs(input.y) < DEAD_ZONE) return;

    }
    //  拡大
    private void ShapeScale()
    {
        //  入力を受け取る
        float input = 0.0f;

        if (gamepad.rightTrigger.ReadValue() > DEAD_ZONE && 
            selectObject.transform.localScale.x < defSca.x * 1.5f) input = gamepad.rightTrigger.ReadValue();
        else if (gamepad.leftTrigger.ReadValue() > DEAD_ZONE &&
            selectObject.transform.localScale.x > defSca.x * 0.5f) input = -gamepad.leftTrigger.ReadValue();
        else return;

        selectObject.transform.localScale += (Vector3.one * input * Time.deltaTime * SCA_SPEED * defSca.x);
    }
}
