<template>
  <div class="container mt-5" style="max-width:600px">
    <div class="row">
      <div class="col-12">
        <h1>TallyConfig </h1>
        <p>
          <button type="button" class="mr-1 btn btn-primary" @click="stopTally" :disabled="loading">STOP Tally Anfragen</button>
          <button type="button" class="mr-1 btn btn-primary" @click="startTally" :disabled="loading">START Tally Anfragen</button>
          <button type="button" class="mr-1 btn btn-primary" @click="restartTally" :disabled="loading">RESTART System</button>
          <span v-if="loading" class="spinner-border text-warning" role="status"></span>
        </p>

        <h3>Einstellungen</h3>
        <div class="form-group mb-5">
          <label for="form_value_host">Passwort für das Lesen und Schreiben der Einstellungen</label>
          <input  id="form_value_host" name="tallyPassword" class="form-control" type="password" v-model="secret">
        </div>
        <form :disabled="loading" v-if="secret.length>3">
          <p>
            Eigene IP: <strong v-if="ip">{{ip}}</strong>
          </p>

          <p class="form-group">
            <label for="form_value_mode">Modus</label>
            <input  id="form_value_mode" class="form-control" type="text" v-model="mode">
          </p>

          <p class="form-group">
            <label for="form_value_host">VMix Host-Adresse</label>
            <input  id="form_value_host" class="form-control" type="text" v-model="host">
          </p>
          <p class="form-group">
            <label for="form_value_ip">Key der Kamera/des Kanals</label>
            <input  id="form_value_ip" class="form-control" type="text" v-model="key">
          </p>

          <div>
            <button type="button" class="mr-1 btn btn-secondary" @click="readSettings" :disabled="loading">Lade Einstellungen</button>
            <button type="button" class="mr-1 btn btn-primary" :disabled="loading || host===null || secret.length===0" @click="writeSettings" >Speichere Einstellungen</button>
          </div>
        </form>
      </div>
    </div>

  </div>
</template>

<script>
import axios from 'axios';
export default {
  data: () =>({
    loading : false,
    mode: 1,
    host: null,
    key: null,
    ip: null,
    secret: "",
  }),
  methods:{
    generalRequest(url) {
      if(this.loading) return;
      this.loading = true;
      let request = {
        url: url,
        method: 'GET'
      };
      axios(request)
        .then(() => {
          console.log('OK: '+url);
        })
        .catch(() => {
          console.error('nicht ok');
        })
        .then(() => {//finally
          this.loading = false;
        });
    },
    stopTally() {
      this.generalRequest('/api/stoptally');
    },
    startTally() {
      this.generalRequest('/api/starttally');
    },
    restartTally() {
      if(this.loading) return;
      this.loading = true;
      let request = {
        url: '/api/restart',
        method: 'GET'
      };
      axios(request)
        .then(() => {})
        .catch(() => {});
      
      //we will not get any response so, we need to manually reset loading
      setTimeout(() => {
        this.loading = false;
        this.host = null;
        this.key = null;
        this.ip = null;
      },2000);
    },
    readSettings() {
      if(this.loading) return;
      this.loading = true;
      let request = {
        url: '/api/readsettings',
        method: 'GET',
        auth: {
          username: 'tallylight',
          password: this.secret
        }
      };
      axios(request)
        .then((response) => {
          console.log('readsettings',response.data);
          this.mode = response.data.mode;
          this.host = response.data.host;
          this.key = response.data.key;
          this.ip = response.data.ip;
        })
        .catch(() => {
          alert('Fehler bei der Anfrage');
        })
        .then(() => {//finally
          this.loading = false;
        });
    },
    writeSettings() {
      if(this.loading) return;
      this.loading = true;
      let request = {
        url: '/api/writesettings',
        method: 'GET',
        params: {
          mode: this.mode,
          host: this.host,
          key: this.key,
        },
        auth: {
          username: 'tallylight',
          password: this.secret
        }
      };
      axios(request)
        .then((response) => {
          this.mode = response.data.mode;
          this.host = response.data.host;
          this.key = response.data.key;
          this.ip = response.data.ip;
        })
        .catch(() => {
          alert('Fehler bei der Anfrage');
        })
        .then(() => {//finally
          this.loading = false;
        });
    }
  }
}
</script>
