using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

public class MoveIcon : MonoBehaviour
{
    //  ゲームパッド
    private Gamepad gamepad;

    //  番号
    private int selectShapeNum;

    //  デッドゾーン
    [SerializeField] private float DEAD_ZONE = 0.1f;
    [SerializeField] private float DEAD_ZONE_ADD = 0.5f;
    //  移動速度
    [SerializeField] private float MOVE_SPEED = 5.0f;

    //  図形を追加するUIの位置
    [SerializeField] private List<GameObject> addShapeUIs;

    private float coolTime;
    private float coolTimer;

    // Start is called before the first frame update
    private void Start()
    {
        //  ゲームパッドを取得する
        gamepad = Gamepad.current;
        //  最初は0
        selectShapeNum = 0;

        coolTime = 0.2f;
    }
    private void Update()
    {
        gameObject.transform.Rotate(new Vector3(0.0f, 0.0f, 0.1f));
    }

    //  自由行動
    public void FreeMove()
    {
        //  入力を受け取る
        Vector2 input = InputController();

        //  画面外に移動したときは戻す
        Vector3 icon_pos = gameObject.transform.localPosition;

        //  入力の大きさによって移動量を変更する
        icon_pos.x += input.x * Time.deltaTime * MOVE_SPEED;
        icon_pos.y += input.y * Time.deltaTime * MOVE_SPEED;
        
        //  画像のサイズを取得
        Vector2 icon_size = gameObject.GetComponent<RectTransform>().sizeDelta / 2.0f;

        //  画面の半分を取得
        float width = (float)Screen.width / 2.0f;
        float height = (float)Screen.height / 2.0f;

        //  左右
        if (icon_pos.x + icon_size.x > width) icon_pos.x = width - icon_size.x;
        else if (icon_pos.x - icon_size.x < -width) icon_pos.x = -width + icon_size.x;

        //  上下
        if (icon_pos.y + icon_size.y > height) icon_pos.y = height - icon_size.y;
        else if (icon_pos.y - icon_size.y < -height) icon_pos.y = -height + icon_size.y;

        gameObject.transform.localPosition = icon_pos;
    }

    //  図形を選択する移動
    public int ShapeSelectMove()
    {
        //  クール時間を減らす
        if (coolTimer > 0.0f) coolTimer -= Time.deltaTime;

        //  入力を受け取る
        Vector2 input = InputController();

        //  各入力での番号の変更(左右)
        if (input.x > DEAD_ZONE_ADD && selectShapeNum % 2 != 1 && coolTimer <= 0.0f)
        {
            selectShapeNum++;
            coolTimer = coolTime;
        }
        else if (input.x < -DEAD_ZONE_ADD && selectShapeNum % 2 != 0 && coolTimer <= 0.0f)
        {
            selectShapeNum--;
            coolTimer = coolTime;
        }
        //  各入力での番号の変更(上下)
        else if (input.y < -DEAD_ZONE_ADD && coolTimer <= 0.0f)
        {
            selectShapeNum += 2;
            if (selectShapeNum >= addShapeUIs.Count) selectShapeNum -= 2;
            coolTimer = coolTime;
        }
        else if (input.y > DEAD_ZONE_ADD && coolTimer <= 0.0f)
        {
            selectShapeNum -= 2;
            if (selectShapeNum < 0) selectShapeNum += 2;
            coolTimer = coolTime;
        }

        if (selectShapeNum > addShapeUIs.Count - 1) selectShapeNum = addShapeUIs.Count - 1;

        //  UIの位置を変える
        gameObject.transform.position = addShapeUIs[selectShapeNum].transform.position;

        return selectShapeNum;
    }
    public int SelectData()
    {
        //  クール時間を減らす
        if (coolTimer > 0.0f) coolTimer -= Time.deltaTime;

        //  入力を受け取る
        Vector2 input = InputController();

        //  各入力での番号の変更(左右)
        if (input.x > DEAD_ZONE_ADD && selectShapeNum % 3 != 2 && coolTimer <= 0.0f)
        {
            selectShapeNum++;
            coolTimer = coolTime;
        }
        else if (input.x < -DEAD_ZONE_ADD && selectShapeNum % 3 != 0 && coolTimer <= 0.0f)
        {
            selectShapeNum--;
            coolTimer = coolTime;
        }
        //  各入力での番号の変更(上下)
        else if (input.y < -DEAD_ZONE_ADD && coolTimer <= 0.0f)
        {
            selectShapeNum += 3;
            if (selectShapeNum >= addShapeUIs.Count) selectShapeNum -= 3;
            coolTimer = coolTime;
        }
        else if (input.y > DEAD_ZONE_ADD && coolTimer <= 0.0f)
        {
            selectShapeNum -= 3;
            if (selectShapeNum < 0) selectShapeNum += 3;
            coolTimer = coolTime;
        }

        if (selectShapeNum > addShapeUIs.Count - 1) selectShapeNum = addShapeUIs.Count - 1;

        //  UIの位置を変える
        gameObject.transform.position = addShapeUIs[selectShapeNum].transform.position;

        return selectShapeNum;
    }

    public Vector2 InputController()
    {
        //  ゲームパッドを常に取得する
        gamepad = Gamepad.current;
        if (gamepad == null) return Vector2.zero;

        Vector2 input = gamepad.leftStick.ReadValue();

        //  入力が小さかったら無視(デッドゾーン)
        if (Mathf.Abs(input.x) < DEAD_ZONE && Mathf.Abs(input.y) < DEAD_ZONE) return Vector2.zero;

        return input;
    }
}
