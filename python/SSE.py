from sseclient import SSEClient #pip install sselcient
import json
import time
from pymongo import MongoClient as mc #pip install pymongo


mongo_ip = "yourmongoniphere"

client = mc(mongo_ip,27017)
print client
cores = {}

ac = "your_particle_access_code"

get_event = "CAPL_state"
while True:
    try:
        messages = SSEClient(
            'https://api.particle.io/v1/events/%s?access_token=%s' %(get_event,ac) 
            )
        for msg in messages:
            try:
                total = json.loads(msg.data)
                data = json.loads(total['data'])
                data['time'] = time.time()
                data['coreid'] = total['coreid']

                try:
                    client[get_event][ data['coreid'] ].insert(data)
                except Exception as E:
                    print "try to insert:",E

            except Exception as E:
                print "Photon Error"
                data = {'error':str(E),'time':time.time()}
                client[get_event+'_error'].errorlog.insert(data)

    except Exception as E:
        print "Data error: try",E
    time.sleep(5)





