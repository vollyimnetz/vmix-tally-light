<template>
  <div class="container mt-1" style="max-width:600px">
    <nav class="mb-4 text-end">
      <select class="form-select" v-model="lang" style="max-width:150px; display:inline;">
        <option v-for="l in langSelect" :key="l.id" :value="l.id">{{l.name}}</option>
      </select>
    </nav>
    <div class="row">
      <div class="col-12">
        <h1>TallyConfig</h1>
        <p class="">
          <button type="button" class="btn btn-primary me-1 mb-1" @click="stopTally" :disabled="loading">{{i18n.btn_stop}}</button>
          <button type="button" class="btn btn-primary me-1 mb-1" @click="startTally" :disabled="loading">{{i18n.btn_start}}</button>
          <button type="button" class="btn btn-primary me-1 mb-1" @click="restartTally" :disabled="loading">{{i18n.btn_restart}}</button>
          <span v-if="loading" class="spinner-border text-warning" role="status"></span>
        </p>

        <h3>{{i18n.headline_settings}}</h3>
        <div class="form-group mb-5">
        
          <label for="form_value_host" class="block">{{i18n.label_password}}</label>
          <div class="input-group mb-3">
            <input  id="form_value_host" name="tallyPassword" type="password" class="form-control" :placeholder="i18n.placeholder_password" v-model="secret">
            <button class="btn btn-primary" type="button" @click="readSettings">{{i18n.btn_load_settings}}</button>
          </div>
        </div>

        <form :disabled="loading" v-if="successFullLoaded">
          <p>
            {{i18n.label_board_ip}}: <strong v-if="ip">{{ip}}</strong>
          </p>

          <p class="form-group">
            <label for="form_value_mode">{{i18n.label_mode}}</label>
            <select id="form_value_mode" class="form-select" v-model="form.mode" size="4">
              <option value="0">{{i18n.mode_0}}</option>
              <option value="1">{{i18n.mode_1}}</option>
              <option value="2">{{i18n.mode_2}}</option>
              <option value="3">{{i18n.mode_3}}</option>
            </select>
          </p>

          <p class="form-group">
            <label for="form_value_host">{{i18n.label_host}}</label>
            <input  id="form_value_host" class="form-control" type="text" v-model="form.host">
          </p>
          <p class="form-group">
            <label for="form_value_ip">{{i18n.label_key}}</label>
            <input  id="form_value_ip" class="form-control" type="text" v-model="form.key">
          </p>

          <div>
            <button type="button" class="btn btn-secondary me-1 mb-1" @click="readSettings" :disabled="loading">{{i18n.btn_settings_reload}}</button>
            <button type="button" class="btn btn-primary me-1 mb-1" :disabled="loading || form.host===null || secret.length===0" @click="writeSettings" >{{i18n.btn_save_and_restart}}</button>
          </div>
        </form>
      </div>
    </div>

  </div>
</template>

<script>
import axios from 'axios';
import de from '../lang/de.json';
import en from '../lang/en.json';
export default {
  data: () =>({
    loading : false,
    form: {
      mode: 0,
      host: null,
      key: null,
    },
    ip: null,
    secret: "",
    successFullLoaded: false,
    lang: 'en',
    langSelect: [
      { id:'en', name: 'english' },
      { id:'de', name: 'deutsch' },
    ]
  }),
  computed: {
    i18n() {
      switch(this.lang) {
        case 'de': return de;
        default: return en;
      }
    }
  },
  methods:{
    resetForm() {
      this.form = {
        mode: 0,
        host: null,
        key: null,
      };
    },
    generalRequest(url) {
      if(this.loading) return;
      this.loading = true;
      let request = { url: url, method: 'GET' };
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
      let request = { url: '/api/restart', method: 'GET' };
      axios(request)
        .then(() => {})
        .catch(() => {});
      
      //we will not get any response so, we need to manually reset loading
      setTimeout(() => {
        this.loading = false;
      },5000);
    },
    readSettings() {
      if(this.secret.length<1) return;
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
          this.form.mode = response.data.mode;
          this.form.host = response.data.host;
          this.form.key = response.data.key;
          this.ip = response.data.ip;
          this.successFullLoaded = true;
        })
        .catch(() => {
          this.successFullLoaded = false;
          alert(this.i18n.alert_error_on_read_settings);
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
        params: this.form,
        auth: {
          username: 'tallylight',
          password: this.secret
        }
      };
      axios(request)
        .then((response) => {
          this.loading = false;
          this.form.mode = response.data.mode;
          this.form.host = response.data.host;
          this.form.key = response.data.key;
          this.ip = response.data.ip;
          this.successFullLoaded = true;
          this.restartTally();
        })
        .catch(() => {
          this.loading = false;
          this.successFullLoaded = false;
          alert(this.i18n.alert_error_on_write_settings);
        });
    }
  }
}
</script>
