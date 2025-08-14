using System.Collections;
using System.Collections.Generic;
using UnityEngine;

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
                PoolObject.GetComponent<SpawnObject>().InitializeObject();
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
            PoolObject.GetComponent<SpawnObject>().MemorizeSpawnLocation(SpawnLocation);
            PoolObject.GetComponent<SpawnObject>().bIsInitializeSuccess = true;
            return PoolObject;
        }
        else
        {
            Debug.Log("Pool is Empty");
            return null;
        }
    }

    public void ReturnPool(GameObject ReturnObject)
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

    public SpawnObjectPool spawnObjectPool { get; private set; }

    float aspectRatio = 9.0f / 16.0f;

    void Awake()
    {
        spawnObjectPool = new SpawnObjectPool();
        if (SpawnObject)
        {
            spawnObjectPool.InitPool(SpawnObject, this.gameObject);
        }
        NonSpawnArea.transform.localScale = new Vector3(NonSpawnArea.transform.localScale.x, NonSpawnArea.transform.localScale.x * aspectRatio, NonSpawnArea.transform.localScale.z);
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

            for (int i = 0; i < 10; i++)
            {
                spawnPos = GetRandomSpawnLocation(SpawnArea);

                if (!NonSpawnArea.bounds.Contains(spawnPos))
                {
                    spawnObjectPool.UsePool(spawnPos);

                    break;
                }
            }
            yield return new WaitForSeconds(SpawnInterval);
        }
    }

    Vector3 GetRandomSpawnLocation(BoxCollider SpawnBox)
    {
        Vector3 center = SpawnBox.bounds.center;
        Vector3 size = SpawnBox.bounds.size;

        float x = Random.Range(center.x - size.x / 2f, center.x + size.x / 2f);
        float y = Random.Range(center.y - size.y / 2f, center.y + size.y / 2f);
        float z = SpawnBox.transform.position.z;

        return new Vector3(x, y, z);
    }
}