using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using DG.Tweening;

//  �G�̎��
public enum EnemyKind
{
    Enemy01,
    Enemy02,
    Enemy03,
    Enemy04
}
//  �G�̏��
public enum EnemyState
{
    Create,
    Move,
    Attack,
    HitStop,
    Blow,
    Dead
}

//  �G�̃X�e�[�^�X�N���X
[System.Serializable]
public class EnemyStatus
{
    public EnemyKind kind;
    public EnemyState state;
    public int hp;
    public float speed;
    public int power;
}

public class EnemyController : MonoBehaviour
{
    //  RigidBody
    private Rigidbody rd;

    //  �G�̃X�e�[�^�X
    [SerializeField] private EnemyStatus enemyStatus;

    //  �ő�HP
    private int MaxHP;

    //  �v���C���[�̏�������
    private GameObject player;
    //  �v���C���[�X�N���v�g
    private PlayerController playerController;
    //  �ڕW�i�v���C���[�j�̏��
    private Transform target;
    //  �v���C���[�Ƃ̋���
    private Vector2 dis;

    //  �U�����󂯂�
    private bool hit;
    //  �U������񕪂����^����
    private bool attacked;

    //  �G������
    public bool IsDead { get; set; }

    //  �q�b�g�X�g�b�v����
    [SerializeField] private float HITSTOP_TIME;
    //  �q�b�g�X�g�b�v�J�E���^
    private float hitStopTimer;

    //  �Ԃ���ԕ���
    private Vector3 vel;

    //  ��_���G�t�F�N�g
    [SerializeField] private GameObject hitEffect;
    [SerializeField] private GameObject deadHitEffect;
    //  ���S�G�t�F�N�g
    [SerializeField] private GameObject deadEffect;

    //  HP��UI
    [SerializeField]
    private Image GreenGauge;
    [SerializeField]
    private Image RedGauge;

    private Tween redGaugeTween;

    private AudioSource audioSource;

    //  ������
    public void EnemyInit(GameObject Player)
    {
        //  �R���|�[�l���g�擾
        rd = gameObject.GetComponent<Rigidbody>();
        gameObject.GetComponent<TrailRenderer>().enabled = false;
        //  �ŏ��̏�Ԃ�Stop
        enemyStatus.state = EnemyState.Create;

        MaxHP = enemyStatus.hp;

        //  �v���C���[�I�u�W�F�N�g���擾
        player = Player;
        //  �v���C���[�X�N���v�g���擾
        playerController = player.GetComponent<PlayerController>();
        //  �v���C���[��transform�����擾
        target = player.transform;
        //  ������������
        dis = new Vector2();

        //  ��U����Ԃ�false
        hit = false;

        //  ������S�Ď������i�d�͂̓K���j
        rd.constraints = RigidbodyConstraints.None;

        //  �U�����Ă��Ȃ��̂�false
        attacked = false;

        vel = new Vector3();

        hitStopTimer = 0.0f;

        IsDead = false;

        audioSource = gameObject.GetComponent<AudioSource>();
    }

    
    public void EnemyUpdate()
    {
        //  ���S�Ȏ��S��ԂȂ珈�������Ȃ�
        if (enemyStatus.state == EnemyState.Dead) return;

        //  �X�e�[�W�O�ɏo���ꍇ
        if (gameObject.transform.position.x > 30.0f ||
            gameObject.transform.position.x < -30.0f ||
            gameObject.transform.position.z > 30.0f ||
            gameObject.transform.position.z < -30.0f)
        {
            enemyStatus.state = EnemyState.Dead;
        }

            //  �v���C���[�ƓG�̋����iY���W�͍l���Ȃ��j
            dis = new Vector2(target.position.x - gameObject.transform.position.x,
            target.position.z - gameObject.transform.position.z);

        //  �ړ������x�N�g���𐳋K��
        Vector2 velocity = dis.normalized;
        //  �v���C���[�̕���������
        if (enemyStatus.state == EnemyState.Move) gameObject.transform.forward = new Vector3(velocity.x, 0.0f, velocity.y);

        //  ��U����Ԃ�true���v���C���[�̏�Ԃ��U���ł͖���
        if(hit && playerController.GetPlayerState() != PlayerState.Attack) hit = false;

        //  �G�̏�Ԃɂ����鏈��
        switch (enemyStatus.state)
        {
            case EnemyState.Create:

                break;
            case EnemyState.Move:
                //  ���ʕ����̃x�N�g���ֈړ�
                gameObject.GetComponent<Animator>().SetFloat("Move", gameObject.transform.forward.magnitude * enemyStatus.speed, 0.1f, Time.deltaTime);
                //  �U��
                if (dis.magnitude < 2.5f)
                {
                    //  �U����Ԃ�
                    enemyStatus.state = EnemyState.Attack;
                    //  �U���A�j���[�V�����̍Đ�
                    gameObject.GetComponent<Animator>().SetTrigger("Attack");
                }

                break;
            case EnemyState.Attack:

                break;
            case EnemyState.HitStop:
                
                //  �h�炷


                //  ���Ԃ��J�E���g
                hitStopTimer += Time.deltaTime;
                //  ���Ԃ��������Ȃ珈�����Ȃ�
                if (hitStopTimer < HITSTOP_TIME) return;

                //  ���Z�b�g
                hitStopTimer = 0.0f;
                //  ������΂�
                enemyStatus.state = EnemyState.Blow;
                //  �A�j���[�V������i�߂�
                gameObject.GetComponent<Animator>().speed = 0.5f;

                break;
            case EnemyState.Blow:
                gameObject.transform.position = gameObject.transform.position + (vel * Time.deltaTime);
                //  �󒆕������O��
                Vector3 sub = gameObject.transform.position;
                sub.y = 1.0f;
                gameObject.transform.position = sub;

                //  �X�e�[�W�O�ɏo���ꍇ
                if(gameObject.transform.position.x > 30.0f ||
                    gameObject.transform.position.x < -30.0f ||
                    gameObject.transform.position.z > 30.0f ||
                    gameObject.transform.position.z < -30.0f)
                {
                    //  ���S�Ȏ��S���
                    enemyStatus.state = EnemyState.Create;

                    //  �A�j���[�V������i�߂�
                    gameObject.GetComponent<Animator>().speed = 1.0f;
                    //  ���S�A�j���[�V�����̍Đ�
                    gameObject.GetComponent<Animator>().SetTrigger("Dead");
                    //  ���S�G�t�F�N�g
                    GameObject de = Instantiate(deadEffect);
                    de.transform.position = gameObject.transform.position + new Vector3(0.0f, 1.0f, 0.0f);
                    //  ����
                    rd.constraints = RigidbodyConstraints.FreezeAll;
                }

                break;

            case EnemyState.Dead:

                break;
        }
    }

    private void OnTriggerStay(Collider other)
    {
        //  �v���C���[����̍U������
        //  ���������I�u�W�F�N�g�����큕�v���C���[���U����ԁ��܂��������Ă��Ȃ����
        if(other.gameObject.CompareTag("PlayerWeapon") &&
            playerController.GetPlayerState() == PlayerState.Attack &&
            !hit)
        {
            //  ��������
            hit = true;
            audioSource.Play();

            //  �U���͂��擾
            int power = playerController.GetAttackPower();
            //  UI�����炷
            GaugeReduction((float)power);
            //  HP���U���͕�����
            enemyStatus.hp -= power;

            //  ��_���A�j���[�V�����̍Đ�
            gameObject.GetComponent<Animator>().SetTrigger("Hit");
            //  �G�t�F�N�g���o��
            GameObject he = Instantiate(hitEffect);
            he.transform.position = gameObject.transform.position + new Vector3(0.0f, 1.0f, 0.0f);

            //  �̗͂�0�ȉ��ɂȂ�����
            if (enemyStatus.hp <= 0)
            {
                //  ��Ԃ�����
                enemyStatus.state = EnemyState.HitStop;
                IsDead = true;
                //  �A�j���[�V�������~�߂�
                gameObject.GetComponent<Animator>().speed = 0.0f;

                gameObject.GetComponent<TrailRenderer>().enabled = true;

                //  ���S�G�t�F�N�g
                GameObject de = Instantiate(deadHitEffect);
                de.transform.position = gameObject.transform.position + new Vector3(0.0f, 1.0f, 0.0f);

                //  ��]�̂ݐ���
                rd.constraints = RigidbodyConstraints.FreezeRotation;

                //  �Ԃ���΂�������ݒ�
                vel = player.transform.forward * 30.0f;
            }
            else
            {
                //  �U�����Ȃ�L�����Z��
                if (enemyStatus.state == EnemyState.Attack) enemyStatus.state = EnemyState.Move;
            }
        }

        //  �v���C���[�ւ̍U������
        if (enemyStatus.state == EnemyState.Attack &&
            other.gameObject.CompareTag("Player") &&
            !attacked &&
            !playerController.Muteki())
        {
            //  �U�����̃_���[�W
            playerController.Damaged(enemyStatus.power);
            //  �U������
            attacked = true;

            //  �G�t�F�N�g���o��
            GameObject he = Instantiate(hitEffect);
            he.transform.position = player.transform.position + new Vector3(0.0f, 1.0f, 0.0f);

            audioSource.Play();
        }
    }

    private void OnCollisionEnter(Collision collision)
    {
        //  ������̃X�e�[�W�ɒ��n
        if(enemyStatus.state == EnemyState.Create &&
            collision.gameObject.CompareTag("Floor"))
        {
            //  �ړ����
            enemyStatus.state = EnemyState.Move;
            //  Y���W��X�EZ��]���t���[�Y
            rd.constraints = RigidbodyConstraints.FreezePositionY | RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationZ;
        }

        if(enemyStatus.state == EnemyState.Blow && 
            collision.gameObject.CompareTag("Stage"))
        {
            //  ���S�Ȏ��S���
            enemyStatus.state = EnemyState.Create;

            //  �A�j���[�V������i�߂�
            gameObject.GetComponent<Animator>().speed = 1.0f;
            //  ���S�A�j���[�V�����̍Đ�
            gameObject.GetComponent<Animator>().SetTrigger("Dead");
            //  ���S�G�t�F�N�g
            GameObject de = Instantiate(deadEffect);
            de.transform.position = gameObject.transform.position + new Vector3(0.0f, 1.0f, 0.0f);
            //  ����
            rd.constraints = RigidbodyConstraints.FreezeAll;
        }
    }

    //  ���S�A�j���[�V�����̏I��
    void Dead()
    {
        enemyStatus.state = EnemyState.Dead;
    }
    //  �U���A�j���[�V�����̏I��
    void AttackAnimFinish()
    {
        enemyStatus.state = EnemyState.Move;
        attacked = false;
    }

    //  �G�̏�Ԃ�n��
    public EnemyState GetEnemyState()
    {
        return enemyStatus.state;
    }

    public EnemyKind GetEnemyKind()
    {
        return enemyStatus.kind;
    }

    private void GaugeReduction(float reducationValue, float time = 1f)
    {
        var valueFrom = (float)enemyStatus.hp / (float)MaxHP;
        var valueTo = ((float)enemyStatus.hp - reducationValue) / (float)MaxHP;

        // �΃Q�[�W����
        GreenGauge.fillAmount = valueTo;

        if (redGaugeTween != null)
        {
            redGaugeTween.Kill();
        }

        // �ԃQ�[�W����
        redGaugeTween = DOTween.To(
            () => valueFrom,
            x => {
                RedGauge.fillAmount = x;
            },
            valueTo,
            time
        );
    }
}
