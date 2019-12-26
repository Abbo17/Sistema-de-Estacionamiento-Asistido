package ar.edu.unlp.info.pacamag.estacionamientoasistido.actividades;

import android.app.FragmentManager;
import android.net.Uri;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v4.app.Fragment;
import android.view.View;
import android.support.design.widget.NavigationView;
import android.support.v4.view.GravityCompat;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;


import ar.edu.unlp.info.pacamag.estacionamientoasistido.R;
import ar.edu.unlp.info.pacamag.estacionamientoasistido.fragments.CreditsFragment;
import ar.edu.unlp.info.pacamag.estacionamientoasistido.fragments.RegisterFragment;
import ar.edu.unlp.info.pacamag.estacionamientoasistido.fragments.ShowDevicesFragment;
import ar.edu.unlp.info.pacamag.estacionamientoasistido.fragments.UserInterfazFragment;
import ar.edu.unlp.info.pacamag.estacionamientoasistido.interfaces.IComunicacionFragment;
import ar.edu.unlp.info.pacamag.estacionamientoasistido.sqlite.ConexionSQLiteHelper;

public class MainActivity extends AppCompatActivity
        implements NavigationView.OnNavigationItemSelectedListener, IComunicacionFragment,
        ShowDevicesFragment.OnFragmentInteractionListener, UserInterfazFragment.OnFragmentInteractionListener,
        RegisterFragment.OnFragmentInteractionListener, CreditsFragment.OnFragmentInteractionListener {

    ShowDevicesFragment showDevicesFragment;
    UserInterfazFragment userInterfazFragment;
    private String address;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);


        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        ActionBarDrawerToggle toggle = new ActionBarDrawerToggle(
                this, drawer, toolbar, R.string.navigation_drawer_open, R.string.navigation_drawer_close);
        drawer.addDrawerListener(toggle);
        toggle.syncState();

        NavigationView navigationView = (NavigationView) findViewById(R.id.nav_view);
        navigationView.setNavigationItemSelectedListener(this);

        address="";

        showDevicesFragment = new ShowDevicesFragment();
        getSupportFragmentManager().beginTransaction().replace(R.id.contenedorFragment,showDevicesFragment).commit();

        ConexionSQLiteHelper conn = new ConexionSQLiteHelper(this);
    }

    @Override
    public void onBackPressed() {
        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        if (drawer.isDrawerOpen(GravityCompat.START)) {
            drawer.closeDrawer(GravityCompat.START);
        } else {
            super.onBackPressed();
        }
    }
/*
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
*/
    @SuppressWarnings("StatementWithEmptyBody")
    @Override
    public boolean onNavigationItemSelected(MenuItem item) {
        // Handle navigation view item clicks here.
        int id = item.getItemId();
        Fragment miFragment = null;
        boolean seleccionoFragment=true;

        if (id == R.id.idSeleccionarDispositivos) {
            miFragment = new ShowDevicesFragment();

        } else if (id == R.id.idEstacionamiento) {
            miFragment = new UserInterfazFragment();
            Bundle bundleEnvio =new Bundle();
            bundleEnvio.putSerializable("mandoMac",address);
            miFragment.setArguments(bundleEnvio);
        } else if (id == R.id.idRegistroHistorico) {
            miFragment = new RegisterFragment();
        } else if (id == R.id.idCreditos) {
            miFragment = new CreditsFragment();
        } else
            seleccionoFragment = true;

        if (seleccionoFragment)
            getSupportFragmentManager().beginTransaction().replace(R.id.contenedorFragment, miFragment).commit();

        DrawerLayout drawer = findViewById(R.id.drawer_layout);
        drawer.closeDrawer(GravityCompat.START);
        return true;
    }

    @Override
    public void enviarMAC(String mac) {
        address=mac;
        userInterfazFragment = new UserInterfazFragment();
        Bundle bundleEnvio =new Bundle();
        bundleEnvio.putSerializable("mandoMac",mac);
        userInterfazFragment.setArguments(bundleEnvio);
        getSupportFragmentManager().beginTransaction().replace(R.id.contenedorFragment, userInterfazFragment).addToBackStack(null).commit();
    }

    @Override
    public void onFragmentInteraction(Uri uri) {

    }
}