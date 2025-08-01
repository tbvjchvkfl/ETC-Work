using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UIElements;

public class SpawnObjectPool
{
    List<GameObject> ObjPool = new List<GameObject>();
    int PoolSize = 100;

    public void InitPool(GameObject SpawnObject, GameObject Parent)
    {
        if (SpawnObject)
        {
            ObjPool.Clear();
            for (int i = 0; i < PoolSize; i++)
            {
                GameObject PoolObject = GameObject.Instantiate(SpawnObject, Parent.transform);
                PoolObject.SetActive(false);
                ObjPool.Add(PoolObject);
            }
        }
    }

    public GameObject UsePool(Vector3 SpawnLocation)
    {
        if(ObjPool.Count > 0)
        {
            GameObject PoolObject = ObjPool[ObjPool.Count - 1];
            ObjPool.RemoveAt(ObjPool.Count - 1);
            PoolObject.SetActive(true);
            PoolObject.transform.position = SpawnLocation;
            return PoolObject;
        }
        else
        {
            Debug.Log("Pool is Empty");
            return null;
        }
    }

    public void RetuanPool(GameObject ReturnObject)
    {
        if (ReturnObject)
        {
            ObjPool.Add(ReturnObject);
            ReturnObject.SetActive(false);
        }
    }

    public bool CheckEmptyPool()
    {
        if (ObjPool.Count == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

public class OB_SpawnPoint : MonoBehaviour
{
    public BoxCollider SpawnArea;
    public BoxCollider NonSpawnArea;
    public GameObject SpawnObject;

    public float SpawnInterval = 1.0f;

    SpawnObjectPool spawnObjectPool;

    void Awake()
    {
        spawnObjectPool = new SpawnObjectPool();
        if (SpawnObject)
        {
            spawnObjectPool.InitPool(SpawnObject, this.gameObject);
        }
    }

    void Start()
    {
        StartCoroutine(StartSpanwLoop());
    }
    
    IEnumerator StartSpanwLoop()
    {
        while (!spawnObjectPool.CheckEmptyPool())
        {
            Vector3 spawnPos = Vector3.zero;

            for (int i = 0; i < 50; i++)
            {
                spawnPos = GetRandomSpawnLocatiion(SpawnArea);

                if (!NonSpawnArea.bounds.Contains(spawnPos))
                {
                    spawnObjectPool.UsePool(spawnPos);
                    break;
                }
            }
            yield return new WaitForSeconds(SpawnInterval);
        }
    }

    Vector3 GetRandomSpawnLocatiion(BoxCollider SpawnArea)
    {
        Vector3 center = SpawnArea.bounds.center;
        Vector3 size = SpawnArea.bounds.size;

        float x = Random.Range(center.x - size.x / 2f, center.x + size.x / 2f);
        float y = center.y;  // ���� ����, �ʿ�� ���� ���̷� �ٲ㵵 ��
        float z = Random.Range(center.z - size.z / 2f, center.z + size.z / 2f);

        return new Vector3(x, y, z);
    }
}


/*        while (!spawnObjectPool.CheckEmptyPool())
        {
            float RandomLocX = Random.Range(-30.0f, 30.0f);
            float RandomLocZ = Random.Range(-12.0f, 12.0f);
            spawnObjectPool.UsePool(new Vector3(SpawnArea.transform.position.x + RandomLocX, SpawnArea.transform.position.y, SpawnArea.transform.position.z + RandomLocZ));
            yield return new WaitForSeconds(SpawnInterval);
        }*/